#ifndef FREQ_SEQ_H
#define FREQ_SEQ_H

#include <math.h>
#include "constants.h"

float noteToFreq(float noteNumber) {
	return 440 * pow(2, (noteNumber - 69) / 12);
}

const float rate = (float) SAMPLE_RATE;

class FreqSeq {
private:
	int    length;
	float  pos;
	float* steps;

public:
	float out;
	float tempo;

	FreqSeq() {
		tempo  = 140; // bpm
		pos    = 0;
		length = 8;
		steps  = new float[length];

		// TODO: add a method to set step by note number
		steps[0] = noteToFreq(69); //440;
		steps[1] = noteToFreq(57); //220;
		steps[2] = noteToFreq(60); //261.63;
		steps[3] = noteToFreq(64); //329.63;
		steps[4] = noteToFreq(48); //130.81;
		steps[5] = noteToFreq(57); //220.00;
		steps[6] = noteToFreq(52); //164.81;
		steps[7] = noteToFreq(62); //293.66;
	};

	~FreqSeq() {
		delete[] steps;
	};

	float tic() {
		pos += length * tempo / (120 * rate);
		if (pos > length) pos -= length;
		int p = (int) pos;
		// if (p < 0) p = 0;
		// if (p > 7) p = 7;
		out = steps[p];
		return out;
	};
};

#endif
