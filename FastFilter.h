#ifndef FAST_FILTER_H
#define FAST_FILTER_H

class FastFilter {

private:

public:

	double out;
	double s;

	FastFilter() {
		out = 0.0;
		s   = 0.1;
	};

    double tic(double in) {
		out = in * s + out * (1 - s);
		return out;
	};

};

#endif
