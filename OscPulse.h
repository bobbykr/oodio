#ifndef OSC_PULSE_H
#define OSC_PULSE_H

#include "Oscillator.h"


class OscPulse : public Oscillator {

private:

public:

	float width;

	OscPulse() {
		width = 0.5;
	};

    float tic() {
		pos += freq / SAMPLE_RATE;
		if (pos > 1) pos -= 1;
		out = (pos > width) ? 1 : 0;
		return out;
	};
};

#endif
