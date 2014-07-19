/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Reverb model declaration
 *
 * Written by Jezar at Dreampoint, June 2000
 * http://www.dreampoint.co.uk
 * This code is public domain
 */

#ifndef FREEVERB_H
#define FREEVERB_H

#include "comb.h"
#include "allpass.h"
#include "tuning.h"

class Freeverb {
public:
		  Freeverb();
	void  mute();
	void  tic(float input);
	void  tic(float inputL, float inputR);

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

	float outR;
	float outL;

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
	Comb  combL[numCombs];
	Comb  combR[numCombs];

	// Allpass filters
	Allpass	allpassL[numAllpasses];
	Allpass	allpassR[numAllpasses];

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

