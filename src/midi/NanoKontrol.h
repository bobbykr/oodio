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

/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * factory preset control change numbers
 */
const int nk_fad[8] = { 0,  1,  2,  3,  4,  5,  6,  7}; // faders
const int nk_rot[8] = {16, 17, 18, 19, 20, 21, 22, 23}; // rotary potentiometers

const int nk_Sbt[8] = {32, 33, 34, 35, 36, 37, 38, 39}; // "S" buttons / LEDs
const int nk_Mbt[8] = {48, 49, 50, 51, 52, 53, 54, 55}; // "M" buttons / LEDs
const int nk_Rbt[8] = {64, 65, 66, 67, 68, 69, 70, 71}; // "R" buttons / LEDs
const int nk_trp[5] = {12, 13, 14, 15, 16};             // transport  buttons / LEDs
const int nk_nav[5] = {58, 59, 60, 61, 62};             // navigation buttons / LEDs
const int nk_cycle  = 46;                               // cycle button / LED 


/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * class definition
 */
class NanoKontrol {
	
private:
	bool     midiInOpened;
	bool     midiOutOpened;
	HMIDIIN  midiIn;
	HMIDIOUT midiOut;

	void _plot(int, bool);

public:
	void push(int, int, int, int);
	float* bindFloat[120]; // nota: cc 120 ~ 127 are reserved as "Channel Mode Messages"
	NanoKontrol();
	~NanoKontrol();
	void initMidi();
	void bindControl(int, float*);
	void plot(int, int, bool);
};

#endif