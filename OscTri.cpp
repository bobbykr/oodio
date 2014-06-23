#include "OscTri.h"
#include "constants.h"

const float rate = (float) SAMPLE_RATE;

OscTri::OscTri() {
	width = 0.5;
}

float OscTri::tic() {
	pos += freq / rate;
	if (pos > 1) pos -= 1;
	out = 1 - 2 * ((pos < width) ? pos / width : 1 - (pos - width) / (1 - width));
	return out;
}
