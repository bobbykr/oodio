#ifndef RC_FILTER_H
#define RC_FILTER_H

class RCFilter {

private:
	double state;

public:
	double reso;
	double cutoff;
	double out;

	RCFilter() {
		state  = 0.0;
		reso   = 0.4;
		cutoff = 0.5;
		out    = 0.0;
	}

	void setCutoff(int value);
	void setReso(int value);

	double tic(double in) {
		state = (1 - reso * cutoff) * state - cutoff * out + cutoff * in;
		out   = (1 - reso * cutoff) * out   + cutoff * state;
		return out;
	}
};

#endif
