#include "OscPulse.h"
#include "constants.h"

const float rate = (float) SAMPLE_RATE;

OscPulse::OscPulse() {
	width = 0.5;
	cycle = 1;
}

float OscPulse::tic() {
	pos += (cycle * freq) / rate;
	if (pos > cycle) pos -= cycle;
	out = (pos > width) ? 1 : 0;
	return out;
}
