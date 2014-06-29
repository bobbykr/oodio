#ifndef CLOCK_H
#define CLOCK_H
#include "../../constants.h"


class Clock {
private:
	double  pos;

public:
	double out;
	double tempo;

	Clock() {
		out   = 1;
		tempo = 140;
	};

	double tic() {
		pos += tempo / (120 * SAMPLE_RATE);
		if (pos >= 1) {
			out = 1;
			pos -= 1;
		} else {
			out = 0;
		}

		return out;
	};
};

#endif
