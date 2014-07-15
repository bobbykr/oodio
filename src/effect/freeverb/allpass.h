/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Allpass filter implementation
 *
 * Written by Jezar at Dreampoint, June 2000
 * http://www.dreampoint.co.uk
 * This code is public domain
 */

#ifndef ALLPASS_H
#define ALLPASS_H
#include "denormals.h"

class allpass {

private:
	float	*buffer;
	int		bufsize;
	int		bufidx;

public:
	float	feedback;

	allpass() {
		bufidx = 0;
	};

	/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
	 * Bind buffer to all pass filter
	 */
	void setbuffer(float *buf, int size) {
		buffer  = buf; 
		bufsize = size;
	};

	/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
	 * Empty data from buffer
	 */
	void mute() {
		for (int i = 0; i < bufsize; i++) buffer[i] = 0;
	};

	/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
	 * Process one sample
	 * Big to inline - but crucial for speed
	 */
	inline float process(float input) {
		float output;
		float bufout;
		
		bufout = buffer[bufidx];
		UNDENORMALISE(bufout);
		
		output = -input + bufout;
		buffer[bufidx] = input + (bufout * feedback);

		if (++bufidx >= bufsize) bufidx = 0;

		return output;
	};
};
	

#endif
