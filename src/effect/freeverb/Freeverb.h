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
	void  processMix(double *inputL, double *inputR, double *outputL, double *outputR, long numSamples, int skip);
	void  processReplace(double *inputL, double *inputR, double *outputL, double *outputR, long numSamples, int skip);
	void  tic(double input, double* outputL, double* outputR);
	void  tic(double inputL, double inputR, double* outputL, double* outputR);

	void  setRoomSize(double value);
	void  setDamp(double value);
	void  setWet(double value);
	void  setDry(double value);
	void  setWidth(double value);
	void  setMode(double value);

	double getRoomSize();
	double getDamp();
	double getWet();
	double getDry();
	double getWidth();
	double getMode();

private:
	void update();

	double gain;
	double roomSize, roomSize1;
	double damp, damp1;
	double wet, wet1, wet2;
	double dry;
	double width;
	double mode;

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
	double bufCombL1[combTuningL1];
	double bufCombR1[combTuningR1];
	double bufCombL2[combTuningL2];
	double bufCombR2[combTuningR2];
	double bufCombL3[combTuningL3];
	double bufCombR3[combTuningR3];
	double bufCombL4[combTuningL4];
	double bufCombR4[combTuningR4];
	double bufCombL5[combTuningL5];
	double bufCombR5[combTuningR5];
	double bufCombL6[combTuningL6];
	double bufCombR6[combTuningR6];
	double bufCombL7[combTuningL7];
	double bufCombR7[combTuningR7];
	double bufCombL8[combTuningL8];
	double bufCombR8[combTuningR8];

	// Buffers for the allpasses
	double bufAllpassL1[allpassTuningL1];
	double bufAllpassR1[allpassTuningR1];
	double bufAllpassL2[allpassTuningL2];
	double bufAllpassR2[allpassTuningR2];
	double bufAllpassL3[allpassTuningL3];
	double bufAllpassR3[allpassTuningR3];
	double bufAllpassL4[allpassTuningL4];
	double bufAllpassR4[allpassTuningR4];
};

#endif

