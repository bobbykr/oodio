#include "FreqSeq.h"
#include "constants.h"

const float rate = (float) SAMPLE_RATE * 2;
const float cycle = 8;

FreqSeq::FreqSeq() {
	tempo = 140; // bpm
	steps = {440, 220, 261.63, 329.63, 130.81, 220.00, 164.81, 293.66};
	pos = 0;
}

float FreqSeq::tic() {
	pos += cycle * tempo / (240 * rate);
	if (pos > cycle) pos -= cycle;
	int p = (int) pos;
	if (p < 0) p = 0;
	if (p > 7) p = 7;
	return steps[p];
}
