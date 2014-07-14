/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Comb filter class declaration
 *
 * Written by Jezar at Dreampoint, June 2000
 * http://www.dreampoint.co.uk
 * This code is public domain
 */

#ifndef COMB_H
#define COMB_H

#include "denormals.h"

class comb {
private:
	float	filterstore;
	float	damp1;
	float	damp2;
	float	*buffer;
	int		bufsize;
	int		bufidx;

public:
	float	feedback;

	comb() {
		filterstore = 0;
		bufidx      = 0;
	};

	void setbuffer(float *buf, int size) {
		buffer  = buf; 
		bufsize = size;
	};

	void mute() {
		for (int i = 0; i < bufsize; i++) buffer[i] = 0;
	};

	void setdamp(float val) {
		damp1 = val; 
		damp2 = 1 - val;
	};

	float getdamp() {
		return damp1;
	};

	// Big to inline - but crucial for speed
	inline float process(float inp) {
		float output;

		output = buffer[bufidx];
		UNDENORMALISE(output);

		filterstore = (output * damp2) + (filterstore * damp1);
		UNDENORMALISE(filterstore);

		buffer[bufidx] = input + (filterstore * feedback);

		if (++bufidx >= bufsize) bufidx = 0;

		return output;
	};
};


#endif

