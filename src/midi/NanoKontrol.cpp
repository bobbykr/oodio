#include "NanoKontrol.h"
#include <string.h>


/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Constructor
 */
NanoKontrol::NanoKontrol() {
	midiIn  = NULL;
	midiOut = NULL;
	midiInOpened  = false;
	midiOutOpened = false;
	for (int i = 0; i < 120; i++) bindFloat[i] = NULL;
}

/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Detructor.
 * If midi are open, reset and close them.
 */
NanoKontrol::~NanoKontrol() {
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

/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Midi in message callback function
 */
void CALLBACK MidiInCb(HMIDIIN device, uint16_t msg, NanoKontrol* self,
						uint32_t data, uint32_t timestamp) {

	// TODO: also handle MIM_LONGDATA (system exclusive)
	if (msg != MIM_DATA) return;

	int chan = (data >> 0)  & 0x0F; // channel.
	int type = (data >> 4)  & 0x0F; // event type.
	int prm1 = (data >> 8)  & 0x7F; // note number / cc number
	int prm2 = (data >> 16) & 0x7F; // velocity    / cc value

	// store event
	// self->push(chan, type, prm1, prm2);

	// if type is a contol change (11) then check if it is bind.
	if (type == 11 && prm1 < 120 && self->bindFloat[prm1] != NULL) {
		*(self->bindFloat[prm1]) = (float)prm2 / 127.0;
	}
}

void NanoKontrol::push(int channel, int type, int param1, int param2) {
	// TODO
}

/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Bind a control change to a variable
 */
void NanoKontrol::bindControl(int cc, float* bind) {
	bindFloat[cc] = bind;
}

/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Initialise midi in and out.
 */
void NanoKontrol::initMidi() {
	int numDevices;
	int inId;
	int inOut;

	// search for "NanoKontrol" device
	numDevices = midiInGetNumDevs();
	for (int i = 0; i < numDevices; i++) {
		MIDIINCAPS deviceInfo;
		midiInGetDevCaps(i, &deviceInfo, sizeof deviceInfo);
		if (strcmp(deviceInfo.szPname, "nanoKONTROL2 1 SLIDER/KNOB") == 0) {
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
		if (strcmp(deviceInfo.szPname, "nanoKONTROL2 1 SLIDER/KNOB") == 0) {
			if (midiOutOpen(&midiOut, i, 0, 0, CALLBACK_NULL) == MMSYSERR_NOERROR) {
				midiOutOpened = true;
			};
			break;
		};
	}
}

