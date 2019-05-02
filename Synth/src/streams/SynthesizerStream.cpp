#include "SynthesizerStream.h"



namespace Synth {


	SynthesizerStream::SynthesizerStream() : s_index(0), sq_index(0), t_index(0) {}
	SynthesizerStream::~SynthesizerStream() {}

	void SynthesizerStream::addSine(int f) {
		stk::SineWave s;
		s.setFrequency(f);
		sine_waves[s_index] = s;
		s_index++;
	}

	void SynthesizerStream::addSqrt(int f) {
		stk::BlitSquare b;
		b.setFrequency(f);
		sqrt_waves[sq_index] = b;
		sq_index++;
	}

	void SynthesizerStream::addTrig(int f) {
		stk::BlitSaw b;
		b.setFrequency(f);
		trig_waves[t_index] = b;
		t_index++;
	}

	float SynthesizerStream::tick() {
		float total = 0;
		for (unsigned int i = 0; i < s_index; i++) {
			total += sine_waves[i].tick();

		}
		for (unsigned int i = 0; i < sq_index; i++) {
			total += sqrt_waves[i].tick();

		}
		for (unsigned int i = 0; i < t_index; i++) {
			total += trig_waves[i].tick();

		}
		return total / (s_index + sq_index + t_index);
		//TODO check div 0
	}

};

/*int main()
{
	// Set the global sample rate before creating class instances.
	Stk::setSampleRate(44100.0);
	Stk::showWarnings(true);
	int nFrames = 100000;
	RtWvOut* dac = 0;

	try {
		// Define and open the default realtime output device for one-channel playback
		dac = new RtWvOut(1);
	}
	catch (StkError&) {
		exit(1);
	}

	//Adding 3 sine waves
	SineWave s;
	s.setFrequency(400);
	Synth::SynthesizerStream track;
	track.addSine(s);
	s.setFrequency(800);
	track.addSine(s);
	s.setFrequency(1600);
	track.addSine(s);

	//Playing
	for (int i = 0; i < nFrames; i++) {
		try {
			dac->tick(track.tick());
		}
		catch (StkError&) {
			goto cleanup;
		}
	}

cleanup:
	delete dac;
	return 0;
}*/