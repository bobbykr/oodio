#ifndef OSC_PULSE_H
#define OSC_PULSE_H
#include "OscRamp.h"

class OscPulse : public OscRamp {

public:

	OscPulse();
    float tic();
	float width;

private:

};

#endif
