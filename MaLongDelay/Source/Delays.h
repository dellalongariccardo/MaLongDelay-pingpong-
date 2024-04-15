#pragma once
#include <JuceHeader.h>

#define MAX_DELAY_TIME 5.0
#define DEFAULT_TIME   1.0
#define DEFAULT_FB     0.0f
#define DT_SMOOTHING   0.1
#define FB_SMOOTHING   0.01f



class BaseDelay
{
public:
	BaseDelay() {}
	~BaseDelay() {}

	void prepareToPlay(const double sr, const int maxNumSamples)
	{
		sampleRate = sr;
		memorySize = roundToInt(MAX_DELAY_TIME * sr) + maxNumSamples;
		delayMemory.setSize(2, memorySize);
		delayMemory.clear();
		initialize();
	}

	void releaseResources()
	{
		delayMemory.setSize(0, 0);
		memorySize = 0;
	}

	void processBlock(AudioBuffer<float>& buffer)
	{
		// store buffer to delay memory
		store(buffer);

		// pull from delay memory to buffer
		pullTo(buffer);

		// advance writing index
		advanceWritePosition(buffer.getNumSamples());
	}

protected:
	virtual void initialize() { }

	void store(const AudioBuffer<float>& buffer)
	{
		const auto numCh = buffer.getNumChannels();
		const auto numInputSamples = buffer.getNumSamples();

		for (int ch = 0; ch < numCh; ++ch)
			if (writeIndex + numInputSamples <= memorySize)
				delayMemory.copyFrom(ch, writeIndex, buffer, ch, 0, numInputSamples);
			else
			{
				const auto fittingSamples = memorySize - writeIndex;
				const auto remainingSamples = numInputSamples - fittingSamples;

				delayMemory.copyFrom(ch, writeIndex, buffer, ch, 0, fittingSamples);
				delayMemory.copyFrom(ch, 0, buffer, ch, fittingSamples, remainingSamples);
			}
	}

	virtual void pullTo(AudioBuffer<float>& buffer) = 0;

	void advanceWritePosition(const int leap)
	{
		writeIndex += leap;
		writeIndex %= memorySize;
	}

	AudioBuffer<float> delayMemory;

	double sampleRate = 1.0;

	int writeIndex = 0;
	int memorySize = 0;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BaseDelay)
};



class PingPongDelay : public BaseDelay
{
public:
	PingPongDelay()
	{
		delayTimeLeft.setCurrentAndTargetValue(DEFAULT_TIME);
		feedbackLeft.setCurrentAndTargetValue(DEFAULT_FB);
		
		delayTimeRight.setCurrentAndTargetValue(DEFAULT_TIME);
		feedbackRight.setCurrentAndTargetValue(DEFAULT_FB);
	}

	~PingPongDelay() {}

	void setTimeLeft(const double newValue)
	{
		delayTimeLeft.setTargetValue(newValue);
	}

	void setFeedbackLeft(const float newValue)
	{
		feedbackLeft.setTargetValue(newValue);
	}

	void setTimeRight(const double newValue)
	{
		delayTimeRight.setTargetValue(newValue);
	}

	void setFeedbackRight(const float newValue)
	{
		feedbackRight.setTargetValue(newValue);
	}

	

private:
	

	void initialize() override
	{
		delayTimeLeft.reset(sampleRate, DT_SMOOTHING);
		feedbackLeft.reset(sampleRate, FB_SMOOTHING);

		delayTimeRight.reset(sampleRate, DT_SMOOTHING);
		feedbackRight.reset(sampleRate, FB_SMOOTHING);
	}


	void pullTo(AudioBuffer<float>& buffer)
	{
		const auto numSamples = buffer.getNumSamples();
		const auto numChannels = buffer.getNumChannels();

		auto outputData = buffer.getArrayOfWritePointers();
		auto delayData = delayMemory.getArrayOfWritePointers();
		


		for (int smp = 0; smp < numSamples; ++smp)
		{
			auto dtRight = delayTimeRight.getNextValue();
			auto fbRight = feedbackRight.getNextValue();

			auto dtLeft = delayTimeLeft.getNextValue();
			auto fbLeft = feedbackLeft.getNextValue();

			auto actualWriteIndex = (writeIndex + smp) % memorySize;
			auto actualReadIndexLeft = actualWriteIndex - (dtLeft * sampleRate) + memorySize;
			auto actualReadIndexRight = actualWriteIndex - (dtRight * sampleRate) + memorySize;


			auto integerPartLeft = static_cast<int>(actualReadIndexLeft);
			auto fractionalPartLeft = actualReadIndexLeft - integerPartLeft;
			auto ALeft = (integerPartLeft + memorySize) % memorySize;
			auto BLeft = (ALeft + 1) % memorySize;
			auto alphaLeft = fractionalPartLeft / (2.0 - fractionalPartLeft); //coefficiente per allPass

			auto integerPartRight = static_cast<int>(actualReadIndexRight);
			auto fractionalPartRight = actualReadIndexRight - integerPartRight;
			auto ARight = (integerPartRight + memorySize) % memorySize;
			auto BRight = (ARight + 1) % memorySize;
			auto alphaRight = fractionalPartRight / (2.0 - fractionalPartRight);

			double sampleValueLeft, sampleValueRight;




			// Fractional delay by all-pass filter for left channel
			sampleValueLeft = alphaLeft * (delayData[0][BLeft] - oldSample[0]) + delayData[0][ALeft];
			oldSample[0] = sampleValueLeft;

				

			// Fractional delay by all-pass filter for right channel
			sampleValueRight = alphaRight * (delayData[1][BRight] - oldSample[1]) + delayData[1][ARight];
			oldSample[1] = sampleValueRight;

				


			// Copio i dati in output alternando tra i canali destro e sinistro
			outputData[0][smp] = sampleValueLeft;
			outputData[1][smp] = sampleValueRight;

			// Applico il feedback incrociato
			
			delayData[0][actualWriteIndex] += sampleValueRight * fbRight;
			delayData[1][actualWriteIndex] += sampleValueLeft * fbLeft;
				


		}
	}




	

	SmoothedValue<double, ValueSmoothingTypes::Linear> delayTimeLeft;
	SmoothedValue<float, ValueSmoothingTypes::Linear> feedbackLeft;

	SmoothedValue<double, ValueSmoothingTypes::Linear> delayTimeRight;
	SmoothedValue<float, ValueSmoothingTypes::Linear> feedbackRight;

	

	

	float oldSample[2] = { 0.0f, 0.0f };
	
	

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PingPongDelay)
};