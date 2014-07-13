#include <stdint.h>
#ifdef __cplusplus
	#include <cstdlib>
#else
	#include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include <windows.h>     // required before including mmsystem
#include <mmsystem.h>    // multimedia functions for windows

#define round(x) ((x)>=0?(int16_t)((x)+0.5):(int16_t)((x)-0.5))

#include "constants.h"
#include "RenderingContext.h"
#include "AmsFont.h"
#include "Button.h"
#include "Slider.h"
#include "src/oscillator/Oscillator.h"
#include "src/oscillator/OscRamp.h"
#include "src/oscillator/OscPulse.h"
#include "src/oscillator/OscTri.h"
#include "src/filter/FastFilter.h"
#include "src/filter/Analog4Poles.h"
#include "src/filter/RCFilter.h"
#include "src/sequencer/FreqSeq.h"
#include "src/midi/Launchpad.h"

bool     filterActive = true;
int16_t  mute = 1;
double   amp = 0.1;

OscPulse     osc1;
OscTri       osc2;
OscTri       osc3;
FastFilter   glide;
RCFilter     fltr;
FreqSeq      seq;

double       fltrRawCutoff = 0.0;
FastFilter   fltrSmoothCutoff;

double map(double value, double iMin, double iMax, double oMin, double oMax) {
	return oMin + (oMax - oMin) * (value - iMin) / (iMax - iMin);
}


void audioCallback(void* udata, uint8_t* stream0, int len) {

	int16_t* stream = (int16_t*) stream0;

	for (len >>= 1; len; len--) {
		// update controls
		fltr.cutoff = fltrSmoothCutoff.tic(fltrRawCutoff);

		// update sequencer
		double f = seq.tic();
		f = glide.tic(f);
		osc1.freq = f;
		osc2.freq = f / 3.01;

		// update oscillators
		double o1 = osc1.tic();
		double o2 = osc2.tic();
		double o3 = osc3.tic();

		// o3 = (1 - o3) / 2;
		o3 = map(o3, -1, 1, 0, 0.5);
		osc1.width = o3;
		osc2.width = o3;

		// simple mix + amplification
		double o = (o1 + o2);

		// apply filter
		// if (filterActive) o = o - fltr.tic(o);
		if (filterActive) o = fltr.tic(o);
		o *= amp;

		// trim overload
		if (o < -1) o = -1;
		if (o >  1) o =  1;

		// convert to output format
		o = 0x8000 * o * mute;

		// write in buffer
		*stream++ = round(o);
	}
}

void playStop() {
	mute = mute == 0 ? 1 : 0;
}

void activateFilter() {
	filterActive = !filterActive;
}

void cutoff(double value) {
	fltrRawCutoff = value;
	// fltr.freq = value;
	// fltr.cutoff = value;
}

void resonance(double value) {
	fltr.reso = value;
}

void changeLfo(double value) {
	osc3.freq = value;
}


int main(int argc, char* argv[]) {

	// initialize MIDI
	/*HMIDIOUT device;
	int deviceId = 4; // TODO: hardcoded device Id: launchpad
	if (midiOutOpen(&device, deviceId, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) return 1;
	union {
		uint32_t word;
		uint8_t  data[4];
	} midiMsg;

	midiMsg.data[0] = 0x90; // note-on
	midiMsg.data[1] = 1;    // key number
	midiMsg.data[2] = 78;   // velocity
	midiMsg.data[3] = 0;    // unused
	midiOutShortMsg(device, midiMsg.word);*/
	Launchpad launchpad;
	launchpad.initMidi();
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			launchpad.plot(x, y, x, y);
		}
	}

	// initialize SDL video and audio
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) return 1;

	// make sure SDL cleans up before exit
	atexit(SDL_Quit);

	// init audio
	{
		SDL_AudioSpec audioSpec;
		audioSpec.freq     = SAMPLE_RATE;
		audioSpec.format   = AUDIO_S16;
		audioSpec.channels = 1;
		audioSpec.samples  = 512;
		audioSpec.callback = audioCallback;
		SDL_OpenAudio(&audioSpec, NULL);
	}

	osc3.freq  = 0.03;
	osc3.width = 0.9;
	glide.freq = 0.005;
	fltrSmoothCutoff.freq = 0.001;

	SDL_PauseAudio(0); // start audio

	SDL_Surface* screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("oodio", NULL);
	RenderingContext ctx(screen);
	ctx.backgroundColor(0, 0, 127);

	// load images
	AmsFont font("amstradFont.bmp");
	Button  btn(5, 23, "start/stop");
	Button  btnf(5, 25, "filter");
	Slider  sld(5, 27, 10, 0.1, 2);
	Slider  cut(12, 25, 30, 0.0, 1.0);
	Slider  res(16, 23, 26, 0.0, 0.7);
	btn.onClic(&playStop);
	btnf.onClic(&activateFilter);
	sld.onChange(&changeLfo);
	cut.onChange(&cutoff);
	res.onChange(&resonance);

	int midiOutNumDevices = midiOutGetNumDevs();
	int midiInNumDevices  = midiInGetNumDevs();
	font.paper(24); font.pen(1);
	font.print("-------- CONNECTED MIDI OUT DEVICES ---------\n");
	font.paper(1); font.pen(24);
	for (int i = 0; i < midiOutNumDevices; i++) {
		font.print(" ");
		font.printNumber(i);
		font.print(": ");
		MIDIOUTCAPS deviceInfo;
		midiOutGetDevCaps(i, &deviceInfo, sizeof deviceInfo);
		font.print(deviceInfo.szPname);
		font.print("\n");
	}
	font.print("\n");

	font.paper(24); font.pen(1);
	font.print("-------- CONNECTED MIDI IN DEVICES ----------\n");
	font.paper(1); font.pen(24);
	for (int i = 0; i < midiInNumDevices; i++) {
		font.print(" ");
		font.printNumber(i);
		font.print(": ");
		MIDIINCAPS deviceInfo;
		midiInGetDevCaps(i, &deviceInfo, sizeof deviceInfo);
		font.print(deviceInfo.szPname);
		font.print("\n");
	}

	btn.draw(&font);
	btnf.draw(&font);
	font.paper(1);
	font.pen(24);


	// program main loop
	bool run = true;
	while (run) {

		//-------------------------
		// message processing loop
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			// check for messages
			switch (event.type) {
			case SDL_QUIT:
				// exit if the window is closed
				run = false;
				break;

			// check for keypresses
			case SDL_KEYDOWN:
				// exit if ESCAPE is pressed
				if (event.key.keysym.sym == SDLK_ESCAPE) run = false;
				// start / stop sound with F1 key
				else if (event.key.keysym.sym == SDLK_F1) playStop();
				else if (event.key.keysym.sym == SDLK_F2) osc1.freq = 110;
				else if (event.key.keysym.sym == SDLK_F3) osc1.freq = 440;
				// keyboard
				else if (event.key.keysym.sym <= 256 && event.key.keysym.sym >= 0 ) {
					font.print(event.key.keysym.sym);
				}
				break;

			case SDL_MOUSEMOTION:
				// font.locate(event.motion.x / (8 * PIXEL), event.motion.y / (8 * PIXEL));
				// font.paper(-1);
				// font.print('*');
				sld.move(event.motion.x, event.motion.y);
				cut.move(event.motion.x, event.motion.y);
				res.move(event.motion.x, event.motion.y);
				break;
			case SDL_MOUSEBUTTONDOWN:
				btn.clic(event.button.x, event.button.y);
				btnf.clic(event.button.x, event.button.y);
				sld.clic(event.button.x, event.button.y);
				cut.clic(event.button.x, event.button.y);
				res.clic(event.button.x, event.button.y);
				break;
			case SDL_MOUSEBUTTONUP:
				sld.unclic(event.button.x, event.button.y);
				cut.unclic(event.button.x, event.button.y);
				res.unclic(event.button.x, event.button.y);
				break;
			}
		}

		ctx.clear();
		sld.draw(&font);
		cut.draw(&font);
		res.draw(&font);
		ctx.drawImage(font.getImage(), 0, 0);
		ctx.update();

		SDL_Delay(40); // 25 FPS
	}

	// close audio
	SDL_CloseAudio();

	// close midi
	// midiOutReset(device);
	// midiOutClose(device);

	return 0;
}
