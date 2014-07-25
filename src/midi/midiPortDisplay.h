#ifndef MIDI_PORT_DISPLAY_H
#define MIDI_PORT_DISPLAY_H

#include <windows.h>     // required before including mmsystem
#include <mmsystem.h>    // multimedia functions for windows
#include "../gui/AmsFont.h"


void displayMidiPorts(AmsFont* font) {
	int midiOutNumDevices = midiOutGetNumDevs();
	int midiInNumDevices  = midiInGetNumDevs();
	font->paper(24); font->pen(1);
	font->print("-------- CONNECTED MIDI OUT DEVICES ---------\n");
	font->paper(1); font->pen(24);
	for (int i = 0; i < midiOutNumDevices; i++) {
		font->print(" ");
		font->printNumber(i);
		font->print(": ");
		MIDIOUTCAPS deviceInfo;
		midiOutGetDevCaps(i, &deviceInfo, sizeof deviceInfo);
		font->print(deviceInfo.szPname);
		font->print("\n");
	}
	font->print("\n");

	font->paper(24); font->pen(1);
	font->print("-------- CONNECTED MIDI IN DEVICES ----------\n");
	font->paper(1); font->pen(24);
	for (int i = 0; i < midiInNumDevices; i++) {
		font->print(" ");
		font->printNumber(i);
		font->print(": ");
		MIDIINCAPS deviceInfo;
		midiInGetDevCaps(i, &deviceInfo, sizeof deviceInfo);
		font->print(deviceInfo.szPname);
		font->print("\n");
	}
}

#endif
