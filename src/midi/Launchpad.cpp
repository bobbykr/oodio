#include "Launchpad.h"
#include <string.h>    // for string comparaison

#include <stdint.h>
#ifdef __cplusplus
	#include <cstdlib>
#else
	#include <stdlib.h>
#endif

/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Constructor
 */
Launchpad::Launchpad() {
	midiIn  = NULL;
	midiOut = NULL;
	midiInOpened  = false;
	midiOutOpened = false;
}

/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Detructor.
 * If midi are open, reset and close them.
 */
Launchpad::~Launchpad() {
	if (midiInOpened) {
		midiInStop(midiIn);
		midiInReset(midiIn);
		midiInClose(midiIn);
	}

	if (midiOutOpened) {
		midiOutReset(midiOut);
		midiOutClose(midiOut);
	}
}

/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Midi in message callback function
 */
void CALLBACK MidiInCb(HMIDIIN device, uint16_t msg, Launchpad* launchpad, uint32_t param1, uint32_t param2) {
	switch (msg) {
	case MIM_OPEN:
		// TODO
		break;
	case MIM_CLOSE:
		// TODO
		break;
	case MIM_DATA:
		// TODO
		launchpad->plot(1,1,3,3);
		break;
	case MIM_LONGDATA:
		// TODO
		break;
	case MIM_ERROR:
	case MIM_LONGERROR:
		// TODO
		break;
	}

	// TODO
};


/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Initialise midi in and out.
 */
void Launchpad::initMidi() {
	int numDevices;
	int inId;
	int outId;

	// search for "Launchpad" device
	numDevices = midiInGetNumDevs();
	for (int i = 0; i < numDevices; i++) {
		MIDIINCAPS deviceInfo;
		midiInGetDevCaps(i, &deviceInfo, sizeof deviceInfo);
		if (strcmp(deviceInfo.szPname, "Launchpad") == 0) {
			if (midiInOpen(&midiIn, i, (DWORD)MidiInCb, (DWORD)this, CALLBACK_FUNCTION) == MMSYSERR_NOERROR) {
				midiInOpened = true;
				midiInStart(midiIn);
			};
			break;
		};
	}

	numDevices = midiOutGetNumDevs();
	for (int i = 0; i < numDevices; i++) {
		MIDIOUTCAPS deviceInfo;
		midiOutGetDevCaps(i, &deviceInfo, sizeof deviceInfo);
		if (strcmp(deviceInfo.szPname, "Launchpad") == 0) {
			if (midiOutOpen(&midiOut, i, 0, 0, CALLBACK_NULL) == MMSYSERR_NOERROR) {
				midiOutOpened = true;
			};
			break;
		};
	}
}

/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Lid a button in the launchpad matrix.
 * Parameters must respect the defined preconditions.
 *
 * @param {int} x     - x position of button to lid. x : [0..9]
 * @param {int} y     - y position of button to lid. y : [0..8]
 * @param {int} red   - red color amount.   red   : [0..3]
 * @param {int} green - green color amount. green : [0..3]
 */
void Launchpad::plot(int x, int y, int red, int green) {
	if (!midiOutOpened) return;
	uint32_t msg = 0x90; // key-on
	// note number
	msg |= (x + y * 16) << 8;
	// velocity
	msg |= (red + green * 16) << 16;
	midiOutShortMsg(midiOut, msg);
}
