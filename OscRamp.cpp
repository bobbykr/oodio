#include "OscRamp.h"
#include "constants.h"

const float rate = (float) SAMPLE_RATE * 2;

OscRamp::OscRamp() {
	freq = 440;
	phase = 0;
	pos = 0;
	cycle = 2;
}

float OscRamp::tic() {
	pos += (cycle * freq) / rate;
	if (pos > cycle) pos -= cycle;
	return pos - 1;
}

