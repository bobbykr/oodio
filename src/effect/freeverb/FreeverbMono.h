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
	void  tic(double input);

	void  setRoomSize(double value);
	void  setDamp(double value);
	void  setMode(double value);

	double getRoomSize();
	double getDamp();
	double getMode();

	double out;

private:
	void update();

	double gain;
	double roomSize, _roomSize;
	double damp, _damp;
	double mode;

	// The following are all declared inline
	// to remove the need for dynamic allocation
	// with its subsequent error-checking messiness

	// Comb filters
	Comb  comb[numCombs];

	// Allpass filters
	Allpass	allpass[numAllpasses];

	// Buffers for the combs
	double bufComb1[combTuningL1];
	double bufComb2[combTuningL2];
	double bufComb3[combTuningL3];
	double bufComb4[combTuningL4];
	double bufComb5[combTuningL5];
	double bufComb6[combTuningL6];
	double bufComb7[combTuningL7];
	double bufComb8[combTuningL8];

	// Buffers for the allpasses
	double bufAllpass1[allpassTuningL1];
	double bufAllpass2[allpassTuningL2];
	double bufAllpass3[allpassTuningL3];
	double bufAllpass4[allpassTuningL4];
};

#endif

