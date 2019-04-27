#include <unordered_map>
#include <string>
#include <iostream>
#include <cstdlib>
#include "RtWvOut.h"
#include "streams/SynthesizerStream.h"
#include "lexer/Parser.h"
#include "Audio.h";

using namespace std;
using namespace stk;

namespace Synth {

	class Synth {

	public:
		//constructor, destructor
		Synth(): streamIDs(new unordered_map<string, Stream*>()), audio(Audio()), parser(Parser()) {}
		~Synth() { delete streamIDs; }

		

		//methods
		Parser& getParser() {
			return parser;
		}

		Audio& getAudio() {
			return audio;
		}

		void processLine(string& line) {
			
		}
		

	private:
		unordered_map<string, Stream*>* streamIDs;
		Parser parser;
		Audio audio;
		//SynthError evaluate(string& line);
		//void handleError(SynthError& error);
		

	};

	struct SynthError {

	};
}


void parserTest() {

	Synth::Synth s;

	while (1) {
		//get the next line

		//parse the line

		//check what function does it need to do

		//execute function

		//free parsed result


		cout << ">> ";
		string line;
		getline(cin, line);

		auto theLine = s.getParser().process(line);

		cout << "Function: " << theLine->function << endl;
		cout << "Type Of Statement: " << theLine->typeOfStatement << endl;
		cout << "ID: " << theLine->ID << endl;
		cout << "Params: " << theLine->params->size() << endl;
		cout << "Error: " << (theLine->error > 0 ? "true" : "false") << endl;

		delete theLine;
	}
}
int synthTest() {
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
	SineWave* s = new SineWave();
	s->setFrequency(440);
	Synth::SynthesizerStream track;
	track.addSine(*s);
	s->setFrequency(220);
	track.addSine(*s);
	s->setFrequency(880);
	track.addSine(*s);



	//Playing
	for (int i = 0; i < nFrames; i++) {
		try {
			dac->tick(track.tick());
		}
		catch (StkError&) {
			goto cleanup;
		}
	}

	goto cleanup;

cleanup:
	delete dac;
	delete s;
	return 0;
}

int synthTest2() {
	Synth::Synth s;
	Synth::SynthesizerStream synth;
	Synth::SynthesizerStream otherSynth;
	stk::SineWave sine;
	sine.setFrequency(200);
	stk::BlitSquare square;
	square.setFrequency(300);
	stk::BlitSaw saw;
	saw.setFrequency(600);

	synth.addSine(sine);
	//synth.addSqrt(square);
	otherSynth.addTrig(saw);

	s.getAudio().addStream(synth);
	s.getAudio().addStream(otherSynth);

	s.getAudio().startStream();

	cin.get();

	s.getAudio().stopStream();

	return 0;
}

int main() {
	synthTest2();
}



