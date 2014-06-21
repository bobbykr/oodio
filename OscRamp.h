#ifndef OSC_RAMP_H
#define OSC_RAMP_H


class OscRamp {

public:

	OscRamp();
	float tic();

	float freq;
	float phase;

private:

	float pos;
	float cycle;
};

#endif
