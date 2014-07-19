#include "audioUtils.h"
#include <math.h>


float noteToFreq(float noteNumber) {
	return 440 * pow(2, (noteNumber - 69) / 12);
}