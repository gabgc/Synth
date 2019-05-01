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
		Synth(): streamIDs(new unordered_map<string, Stream*>()), audio(Audio(this)), parser(Parser()) {}
		~Synth() { 
			delete streamIDs;  }

		void TerminalInterpreter() {
			int error = 0;
			cout << "Welcome to Synth!" << endl;
			while (error == 0) { //aqui algo debe de haber por si hay un fatal error
				cout << ">" << endl;

				//get the next line
				string line;
				getline(cin, line);

				//parse the line
				ParsedResult* pr = parser.process(line);

				//execute the line
				error = evaluate(pr);
				if (error > 0) {
					handleError(error);
				}

				//free parsed result
				delete pr;
			}
		}

		void FileInterpreter(int argCounter, char** arguments) {
			//TODO: Pedro
		}

		//methods
		Parser& getParser() {
			return parser;
		}

		Audio& getAudio() {
			return audio;
		}

		unordered_map<string, Stream*>* getIDs() {
			return streamIDs;
		}
		
	private:
		unordered_map<string, Stream*>* streamIDs;
		Parser parser;
		Audio audio;

		//evaluates the line, returns 0 if there was no error, other wise return error code
		int evaluate(ParsedResult* pr) {
			if (pr->error == 0) {
				int error = 0;
				//HERE GOES ALL THE HARD CODED FUNCTIONALITY
				switch (pr->typeOfStatement) {

				case 0: { //InitStream
					//TODO: Tua & Jaime

				}
				case 1: { //Modification
					//TODO: Tua & Jaime

					/*
						MODIFIER FUNCTIONS

						<Synthesizer only> setFrequency(number)
						<Synthesizer only> setAmplitude(number)
						<Synthesizer only> setWave(Sine | Saw | Square)


						
					*/
					break;
				}
				case 2: { //General Statement
					//TODO: Tua & Jaime
					/*
						GENERAL FUNCTIONS

						play(stream, number)
						play(stream)
						pause(stream)
						removeStream(stream)
						

					*/
					break;
				}
				default:
					break;
				}

				return error;
			} 
			else {
				return pr->error;
			}
		}
		void handleError(int error) {

		}
	};

	struct SynthError {
		//TODO: Gabriel
	};
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

	return 0;
}

int main(int argc, char** argv) {
	Synth::Synth synth;
	argc == 1 ? synth.TerminalInterpreter() : synth.FileInterpreter(argc, argv);
}



