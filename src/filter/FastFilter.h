#ifndef FAST_FILTER_H
#define FAST_FILTER_H

class FastFilter {

private:
	float* input;

public:

	float out;
	float freq;

	FastFilter() {
		out  = 0.0;
		freq = 0.1;
	};

	void connectInput(float* in) {
		input = in;
	}

	inline void tic() {
		out = (*input) * freq + out * (1 - freq);
	};

};

#endif
