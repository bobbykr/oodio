#ifndef COMB_FILTER_H
#define COMB_FILTER_H

class CombFilter {

public:

	CombFilter();
    float tic(float);

	float out;
	float feedbackGain;
	float feedforwardGain;

private:
	float  delay1[100];
	float  delay2[100];

	int    posIn;
	int    posOut;
};

#endif
