#include "OscRamp.h"
#include "constants.h"

const float rate = (float) SAMPLE_RATE * 2;

OscRamp::OscRamp() {
	freq = 440;
	_phase = 0;
	_pos = 0;
	_cycle = 2;
}

float OscRamp::tic() {
	_pos += (_cycle * freq) / rate;
	if (_pos > _cycle) _pos -= _cycle;
	return _pos - 1;
}

/*void OscRamp::freq(float f) {
	_freq = f;
}*/