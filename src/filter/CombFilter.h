#ifndef COMB_FILTER_H
#define COMB_FILTER_H

class CombFilter {

private:
	double delay1;
	double delay2;

public:
	double out;

	double gain;
	double feedback;
	double feedforward;

	CombFilter() {
		out         = 0.0;
		delay1      = 0.0;
		delay2      = 0.0;

		gain        = 0.2;
		feedback    = 0.4;
		feedforward = 0.4;

	};

    double tic(double in) {
		delay2 = out;
		out = in * gain + feedforward * delay1 - feedback * delay2;
		delay1 = in;
		return out;
	};
};

#endif
