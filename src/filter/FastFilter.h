#ifndef FAST_FILTER_H
#define FAST_FILTER_H

class FastFilter {

private:

public:

	float out;
	float freq;

	FastFilter() {
		out  = 0.0;
		freq = 0.1;
	};

    inline float tic(float in) {
		out = in * freq + out * (1 - freq);
		return out;
	};

};

#endif
