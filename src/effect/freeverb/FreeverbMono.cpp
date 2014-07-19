/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Monophononic Freeverb Reverb model implementation
 *
 * Based of Freeverb by Jezar at Dreampoint
 *
 * This code is public domain
 */

#include "FreeverbMono.h"


/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Constructor
 */
FreeverbMono::FreeverbMono() {
	// Tie the components to their buffers
	comb[0].setBuffer(bufComb1, combTuningL1);
	comb[1].setBuffer(bufComb2, combTuningL2);
	comb[2].setBuffer(bufComb3, combTuningL3);
	comb[3].setBuffer(bufComb4, combTuningL4);
	comb[4].setBuffer(bufComb5, combTuningL5);
	comb[5].setBuffer(bufComb6, combTuningL6);
	comb[6].setBuffer(bufComb7, combTuningL7);
	comb[7].setBuffer(bufComb8, combTuningL8);

	allpass[0].setBuffer(bufAllpass1, allpassTuningL1);
	allpass[1].setBuffer(bufAllpass2, allpassTuningL2);
	allpass[2].setBuffer(bufAllpass3, allpassTuningL3);
	allpass[3].setBuffer(bufAllpass4, allpassTuningL4);

	// Set default values
	allpass[0].feedback = 0.5;
	allpass[1].feedback = 0.5;
	allpass[2].feedback = 0.5;
	allpass[3].feedback = 0.5;

	setRoomSize(initialRoom);
	setDamp(initialDamp);
	setMode(initialMode);

	// Buffer will be full of rubbish - so we MUST mute them
	mute();
}


/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Mute
 */
void FreeverbMono::mute() {
	if (getMode() >= freezeMode) return;

	for (int i = 0; i < numCombs; i++) {
		comb[i].mute();
	}

	for (int i = 0; i < numAllpasses; i++) {
		allpass[i].mute();
	}
}

void FreeverbMono::connect(float* in) {
	input = in;
}

/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Process one sample
 *
 * @param {float} input
 */
void FreeverbMono::tic() {
	float o = 0.0;

	// Accumulate comb filters in parallel
	for (int i = 0; i < numCombs; i++) {
		o += comb[i].tic(*input);
	}

	// Feed through allpasses in series
	for (int i = 0; i < numAllpasses; i++) {
		o = allpass[i].tic(o);
	}

	// Set output
	out = o;
}


/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Recalculate internal values after parameter change.
 */
void FreeverbMono::update() {
	int i;

	if (mode >= freezeMode) {
		_roomSize = 1.0;
		_damp     = 0.0;
		gain      = muted;
	} else {
		_roomSize = roomSize;
		_damp     = damp;
		gain      = fixedGain;
	}

	for (i = 0; i < numCombs; i++) {
		comb[i].feedback = _roomSize;
	}

	for (i = 0; i < numCombs; i++) {
		comb[i].setDamp(_damp);
	}
}


/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * The following get/set functions are not inlined, because
 * speed is never an issue when calling them, and also
 * because as you develop the reverb model, you may
 * wish to take dynamic action when they are called.
 */

void FreeverbMono::setRoomSize(float value) {
	roomSize = (value * scaleRoom) + offsetRoom;
	update();
}

float FreeverbMono::getRoomSize() {
	return (roomSize - offsetRoom) / scaleRoom;
}

void FreeverbMono::setDamp(float value) {
	damp = value * scaleDamp;
	update();
}

float FreeverbMono::getDamp() {
	return damp / scaleDamp;
}

void FreeverbMono::setMode(float value) {
	mode = value;
	update();
}

float FreeverbMono::getMode() {
	if (mode >= freezeMode) return 1;
	else                    return 0;
}

