/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Native Instruments Kontrol F1 comprehensive manager.
 *
 * @author Cedric Stoquer
 */

#ifndef KONTROL_F1_H
#define KONTROL_F1_H

#include <stdint.h>    // integer type aliases
#include <windows.h>   // required by mmsystem
#include <mmsystem.h>  // multimedia functions for windows



class Kontrol F1 {
	
private:
	bool     midiInOpened;
	bool     midiOutOpened;
	HMIDIIN  midiIn;
	HMIDIOUT midiOut;

public:
	uint8_t padH[16]; // pad color Hue
	uint8_t padS[16]; // pad color Saturation
	uint8_t padB[16]; // pad color Brightness

	Kontrol F1();
	~Kontrol F1();
	void initMidi();
	void sendControl(int channel, int number, int value);
	void sendNote(int channel, int note, int velocity);
	void setPadColor(int pad, int hue, int saturation, int brightness)
};

#endif