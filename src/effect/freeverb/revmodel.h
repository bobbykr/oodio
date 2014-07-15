/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Reverb model declaration
 *
 * Written by Jezar at Dreampoint, June 2000
 * http://www.dreampoint.co.uk
 * This code is public domain
 */

#ifndef REVMODEL_H
#define REVMODEL_H

#include "comb.hpp"
#include "allpass.hpp"
#include "tuning.h"

class revmodel {
public:
		  revmodel();
	void  mute();
	void  processMix(float *inputL, float *inputR, float *outputL, float *outputR, long numSamples, int skip);
	void  processReplace(float *inputL, float *inputR, float *outputL, float *outputR, long numSamples, int skip);

	void  setRoomSize(float value);
	void  setDamp(float value);
	void  setWet(float value);
	void  setDry(float value);
	void  setWidth(float value);
	void  setMode(float value);

	float getRoomSize();
	float getDamp();
	float getWet();
	float getDry();
	float getWidth();
	float getMode();

private:
	void update();

	float gain;
	float roomSize, roomSize1;
	float damp, damp1;
	float wet, wet1, wet2;
	float dry;
	float width;
	float mode;

	// The following are all declared inline 
	// to remove the need for dynamic allocation
	// with its subsequent error-checking messiness

	// Comb filters
	comb  combL[numCombs];
	comb  combR[numCombs];

	// Allpass filters
	allpass	allpassL[numAllpasses];
	allpass	allpassR[numAllpasses];

	// Buffers for the combs
	float bufCombL1[combTuningL1];
	float bufCombR1[combTuningR1];
	float bufCombL2[combTuningL2];
	float bufCombR2[combTuningR2];
	float bufCombL3[combTuningL3];
	float bufCombR3[combTuningR3];
	float bufCombL4[combTuningL4];
	float bufCombR4[combTuningR4];
	float bufCombL5[combTuningL5];
	float bufCombR5[combTuningR5];
	float bufCombL6[combTuningL6];
	float bufCombR6[combTuningR6];
	float bufCombL7[combTuningL7];
	float bufCombR7[combTuningR7];
	float bufCombL8[combTuningL8];
	float bufCombR8[combTuningR8];

	// Buffers for the allpasses
	float bufAllpassL1[allpassTuningL1];
	float bufAllpassR1[allpassTuningR1];
	float bufAllpassL2[allpassTuningL2];
	float bufAllpassR2[allpassTuningR2];
	float bufAllpassL3[allpassTuningL3];
	float bufAllpassR3[allpassTuningR3];
	float bufAllpassL4[allpassTuningL4];
	float bufAllpassR4[allpassTuningR4];
};

#endif

