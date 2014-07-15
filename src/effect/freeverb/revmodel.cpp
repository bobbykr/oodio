/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Reverb model implementation
 *
 * Written by Jezar at Dreampoint, June 2000
 * http://www.dreampoint.co.uk
 * This code is public domain
 */

#include "revmodel.hpp"


/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Constructor
 */
revmodel::revmodel() {
	// Tie the components to their buffers
	combL[0].setbuffer(bufCombL1, combTuningL1);
	combR[0].setbuffer(bufCombR1, combTuningR1);
	combL[1].setbuffer(bufCombL2, combTuningL2);
	combR[1].setbuffer(bufCombR2, combTuningR2);
	combL[2].setbuffer(bufCombL3, combTuningL3);
	combR[2].setbuffer(bufCombR3, combTuningR3);
	combL[3].setbuffer(bufCombL4, combTuningL4);
	combR[3].setbuffer(bufCombR4, combTuningR4);
	combL[4].setbuffer(bufCombL5, combTuningL5);
	combR[4].setbuffer(bufCombR5, combTuningR5);
	combL[5].setbuffer(bufCombL6, combTuningL6);
	combR[5].setbuffer(bufCombR6, combTuningR6);
	combL[6].setbuffer(bufCombL7, combTuningL7);
	combR[6].setbuffer(bufCombR7, combTuningR7);
	combL[7].setbuffer(bufCombL8, combTuningL8);
	combR[7].setbuffer(bufCombR8, combTuningR8);
	allpassL[0].setbuffer(bufAllpassL1, allpassTuningL1);
	allpassR[0].setbuffer(bufAllpassR1, allpassTuningR1);
	allpassL[1].setbuffer(bufAllpassL2, allpassTuningL2);
	allpassR[1].setbuffer(bufAllpassR2, allpassTuningR2);
	allpassL[2].setbuffer(bufAllpassL3, allpassTuningL3);
	allpassR[2].setbuffer(bufAllpassR3, allpassTuningR3);
	allpassL[3].setbuffer(bufAllpassL4, allpassTuningL4);
	allpassR[3].setbuffer(bufAllpassR4, allpassTuningR4);

	// Set default values
	allpassL[0].feedback = 0.5f;
	allpassR[0].feedback = 0.5f;
	allpassL[1].feedback = 0.5f;
	allpassR[1].feedback = 0.5f;
	allpassL[2].feedback = 0.5f;
	allpassR[2].feedback = 0.5f;
	allpassL[3].feedback = 0.5f;
	allpassR[3].feedback = 0.5f;

	setWet(initialWet);
	setRoomSize(initialRoom);
	setDry(initialDry);
	setDamp(initialDamp);
	setWidth(initialWidth);
	setMode(initialMode);

	// Buffer will be full of rubbish - so we MUST mute them
	mute();
}


/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Mute
 */
void revmodel::mute() {
	if (getMode() >= freezeMode) return;

	for (int i = 0; i < numCombs; i++) {
		combL[i].mute();
		combR[i].mute();
	}

	for (i = 0; i < numAllpasses; i++) {
		allpassL[i].mute();
		allpassR[i].mute();
	}
}


/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Calculate output REPLACING anything already there
 */
void revmodel::processReplace(double *inputL, double *inputR, double *outputL, double *outputR, long numSamples, int skip) {
	double outL, outR, input;

	while (numSamples-- > 0) {
		outL  = outR = 0;
		input = (*inputL + *inputR) * gain;

		// Accumulate comb filters in parallel
		for (int i = 0; i < numCombs; i++) {
			outL += combL[i].tic(input);
			outR += combR[i].tic(input);
		}

		// Feed through allpasses in series
		for (i = 0; i < numAllpasses; i++) {
			outL = allpassL[i].tic(outL);
			outR = allpassR[i].tic(outR);
		}

		// Calculate output REPLACING anything already there
		*outputL = outL * wet1 + outR * wet2 + *inputL * dry;
		*outputR = outR * wet1 + outL * wet2 + *inputR * dry;

		// Increment sample pointers, allowing for interleave (if any)
		inputL  += skip;
		inputR  += skip;
		outputL += skip;
		outputR += skip;
	}
}


/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Calculate output MIXING with anything already there
 */
void revmodel::processMix(double *inputL, double *inputR, double *outputL, double *outputR, long numSamples, int skip) {
	double outL, outR, input;

	while (numSamples-- > 0) {
		outL  = 0;
		outR  = 0;
		input = (*inputL + *inputR) * gain;

		// Accumulate comb filters in parallel
		for (int i = 0; i < numCombs; i++) {
			outL += combL[i].tic(input);
			outR += combR[i].tic(input);
		}

		// Feed through allpasses in series
		for (i = 0; i < numAllpasses; i++) {
			outL = allpassL[i].tic(outL);
			outR = allpassR[i].tic(outR);
		}

		// Calculate output MIXING with anything already there
		*outputL += outL * wet1 + outR * wet2 + *inputL * dry;
		*outputR += outR * wet1 + outL * wet2 + *inputR * dry;

		// Increment sample pointers, allowing for interleave (if any)
		inputL  += skip;
		inputR  += skip;
		outputL += skip;
		outputR += skip;
	}
}

/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Process one sample only, MONO input
 *
 * @param {double}  input   -
 * @param {double*} outputL -
 * @param {double*} outputR -
 */
void revmodel::tic(double input, double* outputL, double* outputR) {
	double outL = 0;
	double outR = 0;

	// Accumulate comb filters in parallel
	for (int i = 0; i < numCombs; i++) {
		outL += combL[i].tic(input);
		outR += combR[i].tic(input);
	}

	// Feed through allpasses in series
	for (i = 0; i < numAllpasses; i++) {
		outL = allpassL[i].tic(outL);
		outR = allpassR[i].tic(outR);
	}

	// Calculate output
	*outputL = outL * wet1 + outR * wet2;
	*outputR = outR * wet1 + outL * wet2;

	return out;
}

/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Process one sample only, STEREO input
 *
 * @param {double}  inputL  -
 * @param {double}  inputR  -
 * @param {double*} outputL -
 * @param {double*} outputR -
 */
void revmodel::tic(double inputL, double inputR, double* outputL, double* outputR) {
	double outL = 0;
	double outR = 0;

	// Accumulate comb filters in parallel
	for (int i = 0; i < numCombs; i++) {
		outL += combL[i].tic(inputL);
		outR += combR[i].tic(inputR);
	}

	// Feed through allpasses in series
	for (i = 0; i < numAllpasses; i++) {
		outL = allpassL[i].tic(outL);
		outR = allpassR[i].tic(outR);
	}

	// Calculate output
	*outputL = outL * wet1 + outR * wet2;
	*outputR = outR * wet1 + outL * wet2;

	return out;
}


/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Recalculate internal values after parameter change.
 */
void revmodel::update() {
	int i;

	wet1 = wet * (width / 2 + 0.5f);
	wet2 = wet * ((1 - width) / 2);

	if (mode >= freezeMode) {
		roomSize1 = 1;
		damp1     = 0;
		gain      = muted;
	} else {
		roomSize1 = roomSize;
		damp1     = damp;
		gain      = fixedGain;
	}

	for (i = 0; i < numCombs; i++) {
		combL[i].feedback = roomSize1;
		combR[i].feedback = roomSize1;
	}

	for (i = 0; i < numCombs; i++) {
		combL[i].setDamp(damp1);
		combR[i].setDamp(damp1);
	}
}


/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * The following get/set functions are not inlined, because
 * speed is never an issue when calling them, and also
 * because as you develop the reverb model, you may
 * wish to take dynamic action when they are called.
 */

void revmodel::setRoomSize(double value) {
	roomSize = (value * scaleRoom) + offsetRoom;
	update();
}

double revmodel::getroomSize() {
	return (roomSize - offsetRoom) / scaleRoom;
}

void revmodel::setDamp(double value) {
	damp = value * scaleDamp;
	update();
}

double revmodel::getDamp() {
	return damp / scaleDamp;
}

void revmodel::setWet(double value) {
	wet = value * scaleWet;
	update();
}

double revmodel::getWet() {
	return wet / scaleWet;
}

void revmodel::setDry(double value) {
	dry = value * scaleDry;
}

double revmodel::getDry() {
	return dry / scaleDry;
}

void revmodel::setWidth(double value) {
	width = value;
	update();
}

double revmodel::getWidth() {
	return width;
}

void revmodel::setMode(double value) {
	mode = value;
	update();
}

double revmodel::getMode() {
	if (mode >= freezeMode) return 1;
	else                    return 0;
}

