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

#define round(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))

#include "constants.h"
#include "RenderingContext.h"
#include "AmsFont.h"


uint16_t sawtooth0 = 0;
uint16_t sawtooth1 = 0;
uint8_t amp = 0;

void audioCallback(void* udata, uint8_t* stream, int len) {
	for (; len; len-=2) {
		// *stream++ = ((sawtooth0++ >> 5) + (sawtooth1 >> 4)) * amp;
		*stream++ = (sawtooth0++ >> 5) * amp;
		*stream++ = (sawtooth1++ >> 5) * amp;
		sawtooth1 += 3;
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
		audioSpec.freq     = 44100;
		audioSpec.format   = AUDIO_S16;
		audioSpec.channels = 2;
		audioSpec.samples  = 512;
		audioSpec.callback = audioCallback;
		SDL_OpenAudio(&audioSpec, NULL);
	}

	SDL_PauseAudio(0); // start audio

	SDL_Surface* screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("oodio", NULL);
	RenderingContext ctx(screen);
	ctx.backgroundColor(0, 0, 127);

	// load images
	AmsFont font("amstradFont.bmp");

	font.paper(19);
	font.pen(6);
	font.print("       -----OODIO-----        \n");
	font.paper(1);
	font.pen(24);

	// program main loop
	bool done = false;
	while (!done) {

		//-------------------------
		// message processing loop
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			// check for messages
			switch (event.type) {
			case SDL_QUIT:
				// exit if the window is closed
				done = true;
				break;

			// check for keypresses
			case SDL_KEYDOWN:
				// exit if ESCAPE is pressed
				if (event.key.keysym.sym == SDLK_ESCAPE) done = true;
				// start / stop sound with spacebar key
				else if (event.key.keysym.sym == SDLK_F1) amp = amp == 0 ? 255 : 0;
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
