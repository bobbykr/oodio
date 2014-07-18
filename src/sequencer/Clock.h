#ifndef CLOCK_H
#define CLOCK_H
#include "../../constants.h"


class Clock {
private:
	double pos;
	double tempo;
	double inc;


public:
	double out;

	Clock() {
		out = 0;
		setTempo(140);
	};

	double tic() {
		pos += inc;
		if (pos >= 1) {
			out = 1;
			pos -= 1;
		} else {
			out = 0;
		}

		return out;
	};

	void setTempo(double t) {
		tempo = t;
		inc = tempo / (30 * SAMPLE_RATE);
	};
};

#endif
