#ifndef OSC_RAMP_H
#define OSC_RAMP_H


class OscRamp {

public:

	OscRamp();
	float tic();
	void  freq(float);

	float _freq;
	float _phase;

private:

	float _pos;
	float _cycle;
};

#endif
