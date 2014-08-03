#define _WIN32_WINNT 0x0501
#define WINVER 0x0501

#include <stdint.h>      // integer type aliases
#include <cstdlib>       // standard library
#include <SDL.h>         // sdl library
#include <windows.h>     // required before including mmsystem
#include <mmsystem.h>    // multimedia functions for windows

#define round(x) ((x)>=0?(int16_t)((x)+0.5):(int16_t)((x)-0.5))

#include "constants.h"
#include "src/utils/audioUtils.h"

// --------------- gui --------------
#include "src/gui/RenderingContext.h"
#include "src/gui/AmsFont.h"
#include "src/gui/Button.h"
#include "src/gui/Slider.h"

// ----------- oscillators ----------
#include "src/oscillator/Oscillator.h"
#include "src/oscillator/OscRamp.h"
#include "src/oscillator/OscPulse.h"
#include "src/oscillator/OscTri.h"

// ------------- filters ------------
#include "src/filter/FastFilter.h"
#include "src/filter/Analog4Poles.h"
#include "src/filter/RCFilter.h"

// ------------- envelopes ------------
#include "src/envelope/DecayEnvelope.h"

// ------------- effects ------------
#include "src/effect/freeverb/FreeverbMono.h"
#include "src/effect/freeverb/Freeverb.h"

// ------------ sequencer -----------
#include "src/sequencer/Clock.h"
#include "src/sequencer/FreqSeq.h"

// ------------ controler -----------
#include "src/midi/Launchpad.h"
#include "src/midi/NanoKontrol.h"
#include "src/midi/KontrolF1.h"

#include "src/midi/midiPortDisplay.h"
#include "src/midi/hidDeviceDisplay.h"

bool     filterActive = true;
int16_t  mute = 1;
float    amp = 0.5;
float    tempo = 88;

OscPulse      osc1;
OscTri        osc2;
OscTri        osc3;
FastFilter    glide;
RCFilter      fltr;
Clock         clk;
FreqSeq       seq;
// FreeverbMono  reverb;
Freeverb      reverb;
DecayEnvelope env;

float mix;
float dry;

float        fltrRawCutoff = 0.0;
FastFilter   fltrSmoothCutoff;

KontrolF1 kontrolF1;


inline float mainLimiterDisto(float x) {
	const float m =  2.00;
	const float b = -0.25;
	const float c =  1.50;

	if      (x <= -3) return -2;
	else if (x <  -1) return -b * x * x + c * x - b;
	else if (x <=  1) return  x;
	else if (x <   3) return  b * x * x + c * x + b;
	else              return  2;
}

void audioCallback(void* udata, uint8_t* stream0, int len) {

	int16_t* stream = (int16_t*) stream0;

	for (len >>= 2; len; len--) {
		clk.tic();

		// update controls

		// update sequencer
		seq.tic();
		glide.tic();
		float f = glide.out;
		osc1.freq = f;
		osc2.freq = f / 3.01;

		// update oscillators
		osc1.tic();
		osc2.tic();
		osc3.tic();

		float o1 = osc1.out;
		float o2 = osc2.out;
		float o3 = osc3.out;


		// o3 = (1 - o3) / 2;
		o3 = map(o3, -1, 1, 0, 0.5);
		osc1.width = o3;
		osc2.width = o3;

		// simple mix + amplification
		mix = (o1 + o2);

		// envelope
		env.tic();
		float e = env.out;

		// apply filter
		fltrSmoothCutoff.tic();
		fltr.cutoff = e * fltrSmoothCutoff.out;
		fltr.tic();

		// if (filterActive) dry = mix - fltr.out;  // hi-pass filter
		if (filterActive) dry = fltr.out;        // low-pass filter
		else dry = mix; // no filter

		// amplification envelope
		dry *= e;

		// main amplification
		dry *= amp;

		// apply reverb
		reverb.tic();

		float outL = dry + reverb.outL * 0.11;
		float outR = dry * 0.9 + reverb.outR * 0.14;

		// trim overload
		outL = mainLimiterDisto(outL);
		outR = mainLimiterDisto(outR);
		/*if (outL < -2) outL = -2;
		if (outL >  2) outL =  2;

		if (outR < -2) outR = -2;
		if (outR >  2) outR =  2;*/

		// convert to output format
		outL = 0xFFF * outL * mute;
		outL = round(outL);

		outR = 0xFFF * outR * mute;
		outR = round(outR);

		// write in buffer
		*stream++ = outL;
		*stream++ = outR;
	}
}

void playStop() {
	mute = mute == 0 ? 1 : 0;
}

void activateFilter() {
	filterActive = !filterActive;
}

void changeRoom(float value) {
	reverb.setRoomSize(value);
}

void changeDecay(float value) {
	env.setReleaseTime(value);
}

void changeDamp(float value) {
	reverb.setDamp(value);
}

void changeCurve(float value) {
	env.setCurvature(value);
}

int padSelected = 0;
int currentH = 0;
int currentS = 0;
int currentB = 0;

void f1ChangeH(float value) {
	currentH = (int)(value * 127);
	kontrolF1.setPadColor(padSelected, currentH, currentS, currentB);
}
void f1ChangeS(float value) {
	currentS = (int)(value * 127);
	kontrolF1.setPadColor(padSelected, currentH, currentS, currentB);
}
void f1ChangeB(float value) {
	currentB = (int)(value * 127);
	kontrolF1.setPadColor(padSelected, currentH, currentS, currentB);
}

void selectPad(int pad, bool isPressed) {
	if (isPressed) padSelected = pad;
}


int main(int argc, char* argv[]) {

	// initialize Launchpad MIDI
	Launchpad launchpad;
	launchpad.initMidi();
	// test
	/*for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			launchpad.plot(x * 2,     y * 2,     x, y);
			launchpad.plot(x * 2 + 1, y * 2 + 1, x, y);
		}
	}*/

	NanoKontrol nanoKontrol;
	/*nanoKontrol.initMidi();
	nanoKontrol.bindControl(16, &fltrRawCutoff);
	nanoKontrol.bindControl(17, &(fltr.reso));
	nanoKontrol.bindControl(18, &changeRoom);
	nanoKontrol.bindControl(19, &changeDamp);
	nanoKontrol.bindControl(20, &changeDecay);
	nanoKontrol.bindControl(21, &changeCurve);*/

	kontrolF1.bindControl(30, &fltrRawCutoff);
	kontrolF1.bindControl(31, &(fltr.reso));
	kontrolF1.bindControl(32, &changeRoom);
	kontrolF1.bindControl(33, &changeDamp);
	kontrolF1.bindControl(37, &changeDecay);
	// kontrolF1.bindControl(21, &changeCurve);


	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 3; y++) {
			nanoKontrol.plot(x, y, false);
		}
	}


	kontrolF1.initMidi();
	kontrolF1.bindControl(34, &f1ChangeH);
	kontrolF1.bindControl(35, &f1ChangeS);
	kontrolF1.bindControl(36, &f1ChangeB);

	kontrolF1.bindPads(&selectPad);


	// initialize SDL video and audio
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) return 1;

	// make sure SDL cleans up before exit
	atexit(SDL_Quit);

	// init synth
	osc3.freq  = 0.03;
	osc3.width = 0.9;
	glide.freq = 0.004;
	fltrSmoothCutoff.freq = 0.001;
	env.setReleaseTime(0.3);
	env.setCurvature(0.8);
	clk.setTempo(tempo);
	seq.setTempo(tempo);
	reverb.setRoomSize(0.3);
	reverb.setDamp(0.3);
	mix = 0.0;
	fltr.connect(&mix);
	glide.connect(&(seq.out));
	fltrSmoothCutoff.connect(&fltrRawCutoff);
	env.connect(&(clk.out));
	reverb.connect(&dry);

	// init SDL audio
	{
		SDL_AudioSpec audioSpec;
		audioSpec.freq     = SAMPLE_RATE;   // 44.1 kHz
		audioSpec.format   = AUDIO_S16;     // signed 16 bit
		audioSpec.channels = 2;             // stereo
		audioSpec.samples  = 512;           // buffer size: 512
		audioSpec.callback = audioCallback;
		SDL_OpenAudio(&audioSpec, NULL);
	}

	SDL_PauseAudio(0); // start audio

	SDL_Surface* screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("oodio", NULL);
	RenderingContext ctx(screen);
	ctx.backgroundColor(0, 0, 127);

	// load images
	AmsFont font("img/amstradFont.bmp");
	Button  btn(5, 23, "start/stop");
	Button  btnf(5, 25, "filter");
	Slider  sld(5, 27, 10, 0.1, 2);
	Slider  cut(12, 25, 30, 0.0, 1.0);
	Slider  res(16, 23, 26, 0.0, 0.7);
	btn.onClic(&playStop);
	btnf.onClic(&activateFilter);
	sld.onChange(&(osc3.freq));
	cut.onChange(&fltrRawCutoff);
	res.onChange(&(fltr.reso));

	displayMidiPorts(&font);
	// displayHidDevices(&font);

	btn.draw(&font);
	btnf.draw(&font);
	font.paper(1);
	font.pen(24);


	int nkx = 0;

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


		//----------------------------------
		// nanoKontrol light show
		/*nkx--;
		if (nkx < 0) nkx = 15;
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 3; y++) {
				bool value = ((nkx + x + y) % 16) < 2;
				nanoKontrol.plot(x, y, value);
			}
		}*/
		//----------------------------------

		SDL_Delay(40); // 25 FPS
	}

	// close audio
	SDL_CloseAudio();

	// close midi
	// midiOutReset(device);
	// midiOutClose(device);

	return 0;
}
