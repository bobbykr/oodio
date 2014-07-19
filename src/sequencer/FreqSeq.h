#ifndef FREQ_SEQ_H
#define FREQ_SEQ_H

#include "../../constants.h"
#include "../utils/audioUtils.h"  // noteToFreq


class FreqSeq {
private:
	int     length;
	double  pos;
	double* steps;
	double  tempo;
	double  inc;

public:
	double out;

	FreqSeq() {
		length = 8;
		pos    = 0;
		steps  = new double[length];

		// TODO: add a method to set step by note number
		steps[0] = noteToFreq(69); //440;
		steps[1] = noteToFreq(57); //220;
		steps[2] = noteToFreq(60); //261.63;
		steps[3] = noteToFreq(64); //329.63;
		steps[4] = noteToFreq(48); //130.81;
		steps[5] = noteToFreq(57); //220.00;
		steps[6] = noteToFreq(52); //164.81;
		steps[7] = noteToFreq(62); //293.66;

		setTempo(140); // bpm
	};

	~FreqSeq() {
		delete[] steps;
	};

	double tic() {
		pos += inc;
		if (pos > length) pos -= length;
		int p = (int) pos;
		// if (p < 0) p = 0;
		// if (p > 7) p = 7;
		out = steps[p];
		return out;
	};

	void   setTempo(double t) {
		tempo = t;
		inc = length * tempo / (120 * SAMPLE_RATE);
	};
};


#endif
