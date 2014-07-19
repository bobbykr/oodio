#ifndef RC_FILTER_H
#define RC_FILTER_H

class RCFilter {

private:
	float  state;
	float* input;

public:
	float reso;
	float cutoff;
	float out;

	RCFilter() {
		state  = 0.0;
		reso   = 0.4;
		cutoff = 0.5;
		out    = 0.0;
	}

	void setCutoff(int value);
	void setReso(int value);

	void setInput(float* in) {
		input = in;
	}

	inline void tic() {
		float in = *input;
		state = (1 - reso * cutoff) * state - cutoff * out + cutoff * in;
		out   = (1 - reso * cutoff) * out   + cutoff * state;
	}
};

#endif
