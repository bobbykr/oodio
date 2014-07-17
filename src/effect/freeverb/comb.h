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
	double	filterstore;
	double	damp1;
	double	damp2;
	double	*buffer;
	int		bufsize;
	int		bufidx;

public:
	double	feedback;

	comb() {
		filterstore = 0.0;
		bufidx      = 0;
	};

	void setbuffer(double* buf, int size) {
		buffer  = buf; 
		bufsize = size;
	};

	void mute() {
		for (int i = 0; i < bufsize; i++) buffer[i] = 0.0;
	};

	void setdamp(double val) {
		damp1 = val; 
		damp2 = 1 - val;
	};

	double getdamp() {
		return damp1;
	};

	// Big to inline - but crucial for speed
	inline double tic(double inp) {
		double output;

		output = buffer[bufidx];
		// UNDENORMALISE(output);

		filterstore = (output * damp2) + (filterstore * damp1);
		// UNDENORMALISE(filterstore);

		buffer[bufidx] = input + (filterstore * feedback);

		if (++bufidx >= bufsize) bufidx = 0;

		return output;
	};
};


#endif

