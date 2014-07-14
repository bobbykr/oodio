#ifndef FAST_FILTER_H
#define FAST_FILTER_H

class FastFilter {

private:

public:

	double out;
	double freq;

	FastFilter() {
		out  = 0.0;
		freq = 0.1;
	};

    inline double tic(double in) {
		out = in * freq + out * (1 - freq);
		return out;
	};

};

#endif
