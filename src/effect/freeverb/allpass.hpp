// Allpass filter declaration
//
// Written by Jezar at Dreampoint, June 2000
// http://www.dreampoint.co.uk
// This code is public domain

#ifndef ALLPASS_H
#define ALLPASS_H
#include "denormals.h"

class allpass {
public:
					allpass();
			void	setbuffer(float *buf, int size);
	inline  float	process(float input);
			void	mute();
			void	setfeedback(float val);
			float	getfeedback();
// private:
	float	feedback;
	float	*buffer;
	int		bufsize;
	int		bufidx;
};


// Big to inline - but crucial for speed

inline float allpass::process(float input) {
	float output;
	float bufout;
	
	bufout = buffer[bufidx];
	undenormalise(bufout);
	
	output = -input + bufout;
	buffer[bufidx] = input + (bufout * feedback);

	if (++bufidx >= bufsize) bufidx = 0;

	return output;
}

#endif
