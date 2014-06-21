#include "FreqSeq.h"
#include "constants.h"

const float rate = (float) SAMPLE_RATE;


FreqSeq::FreqSeq() {
	tempo  = 140; // bpm
	pos    = 0;
	length = 8;
	steps  = new float[length];

	// TODO: add a method to set step by note number
	steps[0] = 440;
	steps[1] = 220;
	steps[2] = 261.63;
	steps[3] = 329.63;
	steps[4] = 130.81;
	steps[5] = 220.00;
	steps[6] = 164.81;
	steps[7] = 293.66;
}

FreqSeq::~FreqSeq() {
	delete[] steps;
}


float FreqSeq::tic() {
	pos += length * tempo / (120 * rate);
	if (pos > length) pos -= length;
	int p = (int) pos;
	// if (p < 0) p = 0;
	// if (p > 7) p = 7;
	out = steps[p];
	return out;
}
