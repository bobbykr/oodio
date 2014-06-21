#include "OscPulse.h"
#include "constants.h"

const float rate = (float) SAMPLE_RATE * 2;

OscPulse::OscPulse() {
	width = 0.5;
}

float OscPulse::tic() {
	pos += (cycle * freq) / rate;
	if (pos > cycle) pos -= cycle;
	float output = 1;
	return ((pos / 2) > width) ? 1 : 0;
}
