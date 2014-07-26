#ifndef HID_DEVICE_DISPLAY_H
#define HID_DEVICE_DISPLAY_H

#include <windows.h>
#include <winuser.h>
#include "../gui/AmsFont.h"


void displayHidDevices(AmsFont* font) {

	unsigned int nDevices = 0;
	GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST));

	if (nDevices <= 0) return;

	// Allocate Memory For Device List
	PRAWINPUTDEVICELIST pRawInputDeviceList;
	pRawInputDeviceList = new RAWINPUTDEVICELIST[sizeof(RAWINPUTDEVICELIST) * nDevices];

	// Fill Device List Buffer
	int nResult;
	nResult = GetRawInputDeviceList(pRawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST));

	// Got Device List?
	if (nResult < 0) {
		delete [] pRawInputDeviceList; // Clean Up
		return;
	}

	font->paper(24); font->pen(1);
	font->print("-------- CONNECTED HID DEVICES ---------\n");
	font->paper(1); font->pen(24);

	// Loop Through Device List
	for (int i = 0; i < nDevices; i++) {
		// Get Character Count For Device Name
		unsigned int nBufferSize = 0;
		nResult = GetRawInputDeviceInfo( pRawInputDeviceList[i].hDevice, // Device
										 RIDI_DEVICENAME,                // Get Device Name
										 NULL,                           // NO Buff, Want Count
										 &nBufferSize );                 // Char Count Here

		// Got Device Name?
		if (nResult < 0) continue;

		// Allocate Memory For Device Name
		char* deviceName = new char[ nBufferSize + 1 ];

		// Got Memory
		if (deviceName == NULL) continue;

		// Get Name
		nResult = GetRawInputDeviceInfo( pRawInputDeviceList[i].hDevice, // Device
										 RIDI_DEVICENAME,                // Get Device Name
										 deviceName,                     // Get Name
										 &nBufferSize );                 // Char Count

		// Got Device Name?
		if (nResult < 0) {
			delete [] deviceName; // Clean Up
			continue;
		}

		// Set Device Info & Buffer Size
		RID_DEVICE_INFO rdiDeviceInfo;
		rdiDeviceInfo.cbSize = sizeof( RID_DEVICE_INFO );
		nBufferSize = rdiDeviceInfo.cbSize;

		// Get Device Info
		nResult = GetRawInputDeviceInfo( pRawInputDeviceList[i].hDevice,
										 RIDI_DEVICEINFO,
										 &rdiDeviceInfo,
										 &nBufferSize );

		if (nResult < 0) continue;

		// Mouse
		if (rdiDeviceInfo.dwType == RIM_TYPEMOUSE) {
			font->print(" ");
			font->printNumber(i);
			font->print(": MOUSE: ");
			font->print(deviceName);
			font->print("\n");
		}

		// Keyboard
		else if (rdiDeviceInfo.dwType == RIM_TYPEKEYBOARD) {
			font->print(" ");
			font->printNumber(i);
			font->print(": KEYBOARD: ");
			font->print(deviceName);
			font->print("\n");
		}

		// Some HID
		else /*(rdi.dwType == RIM_TYPEHID)*/ {
			font->print(" ");
			font->printNumber(i);
			font->print(": HID: ");
			font->print(deviceName);
			font->print("\n");
		}

		delete [] deviceName;
	}

	delete [] pRawInputDeviceList;
}

#endif
