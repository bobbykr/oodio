#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "constants.h"


class Oscillator {

protected:
	double pos;

public:
	double freq;
	double phase;
	double out;

	Oscillator() {
		freq  = 440.0;
		phase = 0.0;
		pos   = 0.0;
		out   = 0.0;
	};

	// virtual ~Oscillator();

	virtual double tic() {
		return 0.0;
	};
};

#endif
