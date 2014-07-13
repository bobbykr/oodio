/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Novation Launchpad comprehensive manager.
 *
 * @author Cedric Stoquer
 */

#ifndef LAUNCHPAD_H
#define LAUNCHPAD_H

#include <windows.h>   // required by mmsystem
#include <mmsystem.h>  // multimedia functions for windows

class Launchpad {
	
private:
	bool     midiInOpened;
	bool     midiOutOpened;
	HMIDIIN  midiIn;
	HMIDIOUT midiOut;

public:
	Launchpad();
	~Launchpad();
	void initMidi();
	void plot(int, int, int, int);
};

#endif