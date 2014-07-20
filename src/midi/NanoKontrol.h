/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Korg NanoKontrol 2 manager.
 *
 * @author Cedric Stoquer
 */

#ifndef NANOKONTROL_H
#define NANOKONTROL_H

#include <stdint.h>    // integer type aliases
#include <windows.h>   // required by mmsystem
#include <mmsystem.h>  // multimedia functions for windows



class NanoKontrol {
	
private:
	bool     midiInOpened;
	HMIDIIN  midiIn;


public:
	void push(int, int, int, int);
	float* bindFloat[120]; // nota: cc 120 ~ 127 are reserved as "Channel Mode Messages"
	NanoKontrol();
	~NanoKontrol();
	void initMidi();
	void bindControl(int, float*);
};

#endif