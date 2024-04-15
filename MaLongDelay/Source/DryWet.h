#pragma once
#include <JuceHeader.h>


#define DEFAULT_DW      0.5f
#define SMOOTHING_TIME  0.01f

class DryWet
{
public:
	DryWet() {	}

	~DryWet() { }

	void prepareToPlay(const double sr, const int maxNumSamples)
	{
		drySignal.setSize(2, maxNumSamples);
		drySignal.clear();

		dryLevel.reset(sr, SMOOTHING_TIME);
		wetLevel.reset(sr, SMOOTHING_TIME);

		updateInternalState();
		setDryWetRatio(dryWetRatio);
	}

	void releaseResources()
	{
		drySignal.setSize(0, 0);
	}

	void copyDrySignal(const AudioBuffer<float>& buffer)
	{
		const auto numCh = buffer.getNumChannels();
		const auto numSamples = buffer.getNumSamples();

		for (int ch = 0; ch < numCh; ++ch)
			drySignal.copyFrom(ch, 0, buffer, ch, 0, numSamples);
	}

	void merge(AudioBuffer<float>& buffer)
	{
		const auto numCh = buffer.getNumChannels();
		const auto numSamples = buffer.getNumSamples();

		
		wetLevel.applyGain(buffer, numSamples);
		dryLevel.applyGain(drySignal, numSamples);


		for (int ch = 0; ch < numCh; ++ch)
			buffer.addFrom(ch, 0, drySignal, ch, 0, numSamples);
		
	}

	void setDryWetRatio(const float newValue)
	{
		dryWetRatio = newValue;
		updateInternalState();
	}

private:
	void updateInternalState()
	{

		dryLevel.setTargetValue(sqrt(1 - dryWetRatio));
		wetLevel.setTargetValue(sqrt(dryWetRatio));
	}

	float dryWetRatio = DEFAULT_DW;

	SmoothedValue<float, ValueSmoothingTypes::Linear> dryLevel;
    SmoothedValue<float, ValueSmoothingTypes::Linear> wetLevel;

	AudioBuffer<float> drySignal;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DryWet)
};