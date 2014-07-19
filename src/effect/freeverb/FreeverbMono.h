/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Monophononic Freeverb Reverb model implementation
 *
 * Based of Freeverb by Jezar at Dreampoint
 *
 * This code is public domain
 */

#ifndef FREEVERB_MONO_H
#define FREEVERB_MONO_H

#include "comb.h"
#include "allpass.h"
#include "tuning.h"

class FreeverbMono {
public:
		  FreeverbMono();
	void  mute();
	void  tic();
	void  connect(float* in);

	void  setRoomSize(float value);
	void  setDamp(float value);
	void  setMode(float value);

	float getRoomSize();
	float getDamp();
	float getMode();

	float out;

private:
	void update();

	float* input;

	float gain;
	float roomSize, _roomSize;
	float damp, _damp;
	float mode;

	// The following are all declared inline
	// to remove the need for dynamic allocation
	// with its subsequent error-checking messiness

	// Comb filters
	Comb  comb[numCombs];

	// Allpass filters
	Allpass	allpass[numAllpasses];

	// Buffers for the combs
	float bufComb1[combTuningL1];
	float bufComb2[combTuningL2];
	float bufComb3[combTuningL3];
	float bufComb4[combTuningL4];
	float bufComb5[combTuningL5];
	float bufComb6[combTuningL6];
	float bufComb7[combTuningL7];
	float bufComb8[combTuningL8];

	// Buffers for the allpasses
	float bufAllpass1[allpassTuningL1];
	float bufAllpass2[allpassTuningL2];
	float bufAllpass3[allpassTuningL3];
	float bufAllpass4[allpassTuningL4];
};

#endif

