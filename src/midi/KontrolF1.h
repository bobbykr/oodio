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



class KontrolF1 {
	
private:
	bool     midiInOpened;
	bool     midiOutOpened;
	HMIDIIN  midiIn;
	HMIDIOUT midiOut;


public:
	uint8_t padH[16]; // pad color Hue
	uint8_t padS[16]; // pad color Saturation
	uint8_t padB[16]; // pad color Brightness


	// theses variable are set public because it will be used by midi callback
	float* bindFloat[120];         // binds cc to variables
	void (*bindFunc[120]) (float); // binds cc to functions
	void (*bindPadsFunc) (int, bool);    // binds pads to function

	KontrolF1();
	~KontrolF1();
	void initMidi();
	void sendControl(int channel, int number, int value);
	void sendNote(int channel, int note, int velocity);
	void setPadColor(int pad, int hue, int saturation, int brightness);

	void bindControl(int, float*);           // bind to variable
	void bindControl(int, void(*cb)(float)); // bind to function
	void bindPads(void(*cb)(int, bool));     // bind pads to function
};

#endif