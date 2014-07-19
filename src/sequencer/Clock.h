#ifndef CLOCK_H
#define CLOCK_H
#include "../../constants.h"


class Clock {
private:
	float pos;
	float tempo;
	float inc;


public:
	float out;

	Clock() {
		out = 0;
		setTempo(140);
	}

	void tic() {
		pos += inc;
		if (pos >= 1) {
			out = 1;
			pos -= 1;
		} else {
			out = 0;
		}
	}

	void setTempo(float t) {
		tempo = t;
		inc = tempo / (30 * SAMPLE_RATE);
	}
};

#endif
