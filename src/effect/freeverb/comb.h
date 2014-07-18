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
	double	filterstore;
	double	damp1;
	double	damp2;
	double	*buffer;
	int		bufsize;
	int		bufidx;

public:
	double	feedback;

	Comb() {
		filterstore = 0.0;
		bufidx      = 0;
	};

	void setBuffer(double* buf, int size) {
		buffer  = buf;
		bufsize = size;
	};

	void mute() {
		for (int i = 0; i < bufsize; i++) buffer[i] = 0.0;
	};

	void setDamp(double val) {
		damp1 = val;
		damp2 = 1 - val;
	};

	double getDamp() {
		return damp1;
	};

	// Big to inline - but crucial for speed
	inline double tic(double input) {
		double output;

		output = buffer[bufidx];
		DOUBLE_DENORM(output);

		filterstore = (output * damp2) + (filterstore * damp1);
		DOUBLE_DENORM(filterstore);

		buffer[bufidx] = input + (filterstore * feedback);

		if (++bufidx >= bufsize) bufidx = 0;

		return output;
	};
};


#endif

