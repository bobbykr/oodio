#ifndef OSC_PULSE_H
#define OSC_PULSE_H
#include "Oscillator.h"

class OscPulse : public Oscillator {

public:

	OscPulse();
    float tic();
	float width;

private:

};

#endif
