#include "KontrolF1.h"
#include <string.h>


/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Constructor
 */
KontrolF1::KontrolF1() {
	midiIn  = NULL;
	midiOut = NULL;
	midiInOpened  = false;
	midiOutOpened = false;
	for (int i = 0; i < 16; i++) {
		padH[i] = 0;
		padS[i] = 0;
		padB[i] = 0;
	}
}

/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Detructor.
 * If midi are open, reset and close them.
 */
KontrolF1::~KontrolF1() {
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
void CALLBACK MidiInCb(HMIDIIN device, uint16_t msg, KontrolF1* self,
						uint32_t data, uint32_t timestamp) {

	if (msg != MIM_DATA) return;

	int chan = (data >> 0)  & 0x0F; // channel.
	int type = (data >> 4)  & 0x0F; // event type.
	int note = (data >> 8)  & 0x7F; // event number.
	int velo = (data >> 16) & 0x7F; // velocity / value.

	// TODO
};


/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Initialise midi in and out.
 */
void KontrolF1::initMidi() {
	int numDevices;
	int inId;
	int outId;

	// search for "Traktor Kontrol F1 - 1" device
	numDevices = midiInGetNumDevs();
	for (int i = 0; i < numDevices; i++) {
		MIDIINCAPS deviceInfo;
		midiInGetDevCaps(i, &deviceInfo, sizeof deviceInfo);
		if (strcmp(deviceInfo.szPname, "Traktor Kontrol F1 - 1") == 0) {
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
		if (strcmp(deviceInfo.szPname, "Traktor Kontrol F1 - 1") == 0) {
			if (midiOutOpen(&midiOut, i, 0, 0, CALLBACK_NULL) == MMSYSERR_NOERROR) {
				midiOutOpened = true;
			};
			break;
		};
	}
}


void KontrolF1::sendControl(int channel, int number, int value) {
	if (!midiOutOpened) return;
	// control change : 0xB0
	uint32_t msg = 0xB0 | channel | number << 8 | value << 16;
	midiOutShortMsg(midiOut, msg);
}

void KontrolF1::sendNote(int channel, int note, int velocity) {
	if (!midiOutOpened) return;
	// note : 0x90
	uint32_t msg = 0x90 | channel | note << 8 | velocity << 16;
	midiOutShortMsg(midiOut, msg);
}

void KontrolF1::setPadColor(int pad, int hue, int saturation, int brightness) {
	if (!midiOutOpened) return;
	uint32_t base = 0xB0 | pad << 8;
	if (padH[pad] != hue) {
		padH[pad] = hue;
		uint32_t h = base | 0 | hue << 16;
		midiOutShortMsg(midiOut, h);
	}
	if (padS[pad] != saturation) {
		padS[pad] = saturation;
		uint32_t s = base | 1 | saturation << 16;
		midiOutShortMsg(midiOut, s);
	}
	if (padB[pad] != brightness) {
		padB[pad] = brightness;
		uint32_t b = base | 2 | brightness << 16;
		midiOutShortMsg(midiOut, b);
	}
}