#include "OscRamp.h"
#include "constants.h"

const float rate  = (float) SAMPLE_RATE;


float OscRamp::tic() {
	pos += freq / rate;
	if (pos > 1) pos -= 1;
	out = 2 * pos - 1;
	return out;
}

