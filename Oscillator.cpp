#include "Oscillator.h"
#include "constants.h"


Oscillator::Oscillator() {
	freq  = 440;
	phase = 0;
	pos   = 0;
	cycle = 2;
	out   = 0;
}

float Oscillator::tic() {
	return 0;
}