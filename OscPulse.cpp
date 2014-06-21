#include "OscPulse.h"
#include "constants.h"

const float rate = (float) SAMPLE_RATE;

OscPulse::OscPulse() {
	width = 0.5;
}

float OscPulse::tic() {
	pos += freq / rate;
	if (pos > 1) pos -= 1;
	out = (pos > width) ? 1 : 0;
	return out;
}
