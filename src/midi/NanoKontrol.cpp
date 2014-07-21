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
	for (int i = 0; i < 120; i++) {
		bindFloat[i] = NULL;
		bindFunc[i]  = NULL;
	}
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
	if (type == 11 && prm1 < 120) {
		if (self->bindFloat[prm1] != NULL) {
			*(self->bindFloat[prm1]) = (float)prm2 / 127.0;
		} else if (self->bindFunc[prm1] != NULL) {
			self->bindFunc[prm1]((float)prm2 / 127.0);
		}
	}
}

void NanoKontrol::push(int channel, int type, int param1, int param2) {
	// TODO
}

/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Bind a control change
 */
void NanoKontrol::bindControl(int cc, float* bind) {
	bindFloat[cc] = bind;
}

void NanoKontrol::bindControl(int cc, void(*cb)(float)) {
	bindFunc[cc] = cb;
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
		if (strcmp(deviceInfo.szPname, "nanoKONTROL2 1 CTRL") == 0) {
			if (midiOutOpen(&midiOut, i, 0, 0, CALLBACK_NULL) == MMSYSERR_NOERROR) {
				midiOutOpened = true;
			};
			break;
		};
	}
}

/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * send a midi message to change nanoKontrol's LED status
 */
void NanoKontrol::_plot(int cc, bool status) {
	if (!midiOutOpened) return;
	uint16_t value = status ? 127 : 0;
	// control change on channel 0 (1011cccc)
	uint32_t msg =  0xB0 | cc << 8 | value << 16;
	midiOutShortMsg(midiOut, msg);
}

/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * set LED status
 */
void NanoKontrol::plot(int x, int y, bool status) {
	if      (y == 0) _plot(nk_Sbt[x], status);
	else if (y == 1) _plot(nk_Mbt[x], status);
	else if (y == 2) _plot(nk_Rbt[x], status);
	else if (y == 3) _plot(nk_nav[x], status);
	else if (y == 4) _plot(nk_trp[x], status);
	else             _plot(nk_cycle,  status);
}