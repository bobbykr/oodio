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

class Comb {
private:
	float	filterstore;
	float	damp1;
	float	damp2;
	float	*buffer;
	int		bufsize;
	int		bufidx;

public:
	float	feedback;

	Comb() {
		filterstore = 0.0;
		bufidx      = 0;
	};

	void setBuffer(float* buf, int size) {
		buffer  = buf;
		bufsize = size;
	};

	void mute() {
		for (int i = 0; i < bufsize; i++) buffer[i] = 0.0;
	};

	void setDamp(float val) {
		damp1 = val;
		damp2 = 1 - val;
	};

	float getDamp() {
		return damp1;
	};

	// Big to inline - but crucial for speed
	inline float tic(float input) {
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

