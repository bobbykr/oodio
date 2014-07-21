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
 * Control Change number & LED grid disposition
 *
 *                             (x) 0    1    2    3    4    5    6    7
 *     ┌────────────────────────┬────┬────┬────┬────┬────┬────┬────┬────┐
 *     │                        │ 16 │ 17 │ 18 │ 19 │ 20 │ 21 │ 22 │ 23 │
 *     │                        ├────┼────┼────┼────┼────┼────┼────┼────┤
 *     │  0    1                │ 32 │ 33 │ 34 │ 35 │ 36 │ 37 │ 38 │ 39 │ 0
 *     ├────┬────┐              ├────┼────┼────┼────┼────┼────┼────┼────┤
 *   3 │ 58 │ 59 │  2    3    4 │ 48 │ 49 │ 50 │ 51 │ 52 │ 53 │ 54 │ 55 │ 1
 *     ├────┼────┼────┬────┬────┼────┼────┼────┼────┼────┼────┼────┼────┤
 *   5 │ 46 │ ░░ │ 60 │ 61 │ 62 │ 64 │ 65 │ 66 │ 67 │ 68 │ 69 │ 70 │ 71 │ 2
 *     ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
 *   4 │ 12 │ 13 │ 14 │ 15 │ 16 │    │    │    │    │    │    │    │    │
 *     ├────┴────┴────┴────┴────┤  0 │  1 │  2 │  3 │  4 │  5 │  6 │  7 │ 
 *     │                        │    │    │    │    │    │    │    │    │ 
 *     └────────────────────────┴────┴────┴────┴────┴────┴────┴────┴────┘(y)
 * 
 */
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

	// binds on control changes 0~119.
	// These are public because called in midi callback (TODO: protected?)
	// NOTA: cc 120 ~ 127 are reserved as "Channel Mode Messages"
	float* bindFloat[120];         // binds to variables
	void (*bindFunc[120]) (float); // binds to functions

	NanoKontrol();
	~NanoKontrol();
	void initMidi();
	
	void bindControl(int, float*);           // bind to variable
	void bindControl(int, void(*cb)(float)); // bind to function

	void plot(int, int, bool);
};

#endif