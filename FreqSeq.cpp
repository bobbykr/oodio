#include "FreqSeq.h"
#include "constants.h"
#include <math.h>

float noteToFreq(float noteNumber) {
	return 440 * pow(2, (noteNumber - 69) / 12);
}

FreqSeq::FreqSeq() {
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
}

FreqSeq::~FreqSeq() {
	delete[] steps;
}


float FreqSeq::tic() {
	pos += length * tempo / (120 * SAMPLE_RATE);
	if (pos > length) pos -= length;
	int p = (int) pos;
	// if (p < 0) p = 0;
	// if (p > 7) p = 7;
	out = steps[p];
	return out;
}
