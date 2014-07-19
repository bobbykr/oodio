#ifndef OSC_RAMP_H
#define OSC_RAMP_H

#include "Oscillator.h"


class OscRamp : public Oscillator {
	
private:

public:

	float tic() {
		pos += freq / SAMPLE_RATE;
		if (pos > 1) pos -= 1;
		out = 2 * pos - 1;
		return out;
	};
};

#endif
