#include "audioUtils.h"
#include <math.h>


double noteToFreq(double noteNumber) {
	return 440 * pow(2, (noteNumber - 69) / 12);
}