#ifndef OSCILLATOR_H
#define OSCILLATOR_H


class Oscillator {

public:

	Oscillator();
	// virtual ~Oscillator();
	virtual float tic();

	float freq;
	float phase;
	float out;

protected:

	float pos;
	float cycle;
};

#endif
