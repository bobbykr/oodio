#ifndef OSC_RAMP_H
#define OSC_RAMP_H
#include "Oscillator.h"
#include "constants.h"

const float rate  = (float) SAMPLE_RATE;

class OscRamp : public Oscillator {
	
private:

public:

	float tic() {
		pos += freq / rate;
		if (pos > 1) pos -= 1;
		out = 2 * pos - 1;
		return out;
	};
};

#endif
