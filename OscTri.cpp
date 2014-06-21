#include "OscTri.h"
#include "constants.h"

const float rate = (float) SAMPLE_RATE;

OscTri::OscTri() {
	width = 0.5;
	cycle = 1;
}

float OscTri::tic() {
	pos += (cycle * freq) / rate;
	if (pos > cycle) pos -= cycle;
	return 1 - 2 * ((pos < width) ? pos / width : 1 - (pos - width) / (1 - width));
}
