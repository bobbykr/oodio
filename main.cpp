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

#define round(x) ((x)>=0?(int16_t)((x)+0.5):(int16_t)((x)-0.5))

#include "constants.h"
#include "RenderingContext.h"
#include "AmsFont.h"
#include "OscRamp.h"
#include "FreqSeq.h"


int16_t mute = 0;
float   amp = 0.1;

OscRamp osc1;
OscRamp osc2;
OscRamp osc3;
FreqSeq seq;

void audioCallback(void* udata, uint8_t* stream0, int len) {

	int16_t* stream = (int16_t*) stream0;

	for (len >>= 1; len; len--) {
		// update sequencer
		float f = seq.tic();
		osc1.freq = f;
		osc2.freq = f * 3.01;

		// update oscillators
		float o1 = osc1.tic();
		float o2 = osc2.tic();
		float o3 = osc3.tic();

		o3 = (1 - o3) / 2;

		// simple mix + amplification
		float o = (o1 + o3 * o2);
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


int main(int argc, char** argv) {
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

	osc1.freq = 440;
	osc2.freq = 444;
	osc3.freq = 20;

	SDL_PauseAudio(0); // start audio

	SDL_Surface* screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("oodio", NULL);
	RenderingContext ctx(screen);
	ctx.backgroundColor(0, 0, 127);

	// load images
	AmsFont font("amstradFont.bmp");

	font.paper(19);
	font.pen(6);
	font.locate(6, 8);
	font.print(" -----OODIO----- \n");
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
				else if (event.key.keysym.sym == SDLK_F1) mute = mute == 0 ? 1 : 0;
				else if (event.key.keysym.sym == SDLK_F2) osc1.freq = 110;
				else if (event.key.keysym.sym == SDLK_F3) osc1.freq = 440;
				// keyboard
				else if (event.key.keysym.sym <= 256 && event.key.keysym.sym >= 0 ) {
					font.print(event.key.keysym.sym);
				}
				break;
			}
		}

		ctx.clear();
		ctx.drawImage(font.getImage(), 0, 0);
		ctx.update();

		SDL_Delay(40); // 25 FPS
	}

	SDL_CloseAudio(); // close audio
	return 0;
}
