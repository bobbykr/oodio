#ifndef FAST_FILTER_H
#define FAST_FILTER_H

class FastFilter {

private:

public:

	float out;
	float s;

	FastFilter() {
		out = 0.0;
		s   = 0.1;
	};

    float tic(float in) {
		out = in * s + out * (1 - s);
		return out;
	};

};

#endif
