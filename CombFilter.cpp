#include "CombFilter.h"


CombFilter::CombFilter() {
	out             =  0;
	feedbackGain    =  0.4;
	feedforwardGain = -0.4;

	for (int i = 0; i < 100; i++) {
		delay1[i] = 0;
		delay2[i] = 0;
	}
	posIn  = 0;
	posOut = 1;
}


float CombFilter::tic(float in) {
	delay2[posIn] = out;
	out = in + feedforwardGain * delay1[posOut] + feedbackGain * delay2[posOut];
	delay1[posIn] = in;
	posIn++;
	posOut++;
	if (posIn  >= 100) posIn  = 0;
	if (posOut >= 100) posOut = 0;
	return out;
}
