#include "RCFilter.h"
#include <math.h>


// set cutoff from a MIDI value : [0..127]
void RCFilter::setCutoff(int value) {
	cutoff = pow(0.5, (128 - value) / 16.0);
};

// set resonance from a MIDI value : [0..127]
void RCFilter::setReso(int value) {
	reso = pow(0.5, (value + 24) / 16.0);
};


