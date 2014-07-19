#ifndef COMB_FILTER_H
#define COMB_FILTER_H

class CombFilter {

private:
	float delay1;
	float delay2;
	float* input;

public:
	float out;

	float gain;
	float feedback;
	float feedforward;

	CombFilter() {
		out         = 0.0;
		delay1      = 0.0;
		delay2      = 0.0;

		gain        = 0.2;
		feedback    = 0.4;
		feedforward = 0.4;

	};

	void connectInput(float* in) {
		input = in;
	}

    void tic() {
		delay2 = out;
		out = (*input) * gain + feedforward * delay1 - feedback * delay2;
		delay1 = (*input);
	};
};

#endif
