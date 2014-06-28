#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "constants.h"


class Oscillator {

protected:
	// float rate;
	float pos;

public:
	float freq;
	float phase;
	float out;

	Oscillator() {
		// rate  = (float)SAMPLE_RATE;
		freq  = 440.0;
		phase = 0.0;
		pos   = 0.0;
		out   = 0.0;
	};

	// virtual ~Oscillator();

	virtual float tic() {
		return 0.0;
	};
};

#endif
