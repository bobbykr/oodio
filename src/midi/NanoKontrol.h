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

	void push(int, int, int, int);
	float* bindFloat[128];

public:
	NanoKontrol();
	~NanoKontrol();
	void initMidi();
	void bindControl(int, float*);
};

#endif