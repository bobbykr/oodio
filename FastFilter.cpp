#include "FastFilter.h"


FastFilter::FastFilter() {
	out = 0.0;
	s   = 0.1;
}


float FastFilter::tic(float in) {
	out = in * s + out * (1 - s);
	return out;
}
