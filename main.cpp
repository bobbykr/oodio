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

#include "RenderingContext.h"


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
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("Unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}

	// make sure SDL cleans up before exit
	atexit(SDL_Quit);

	// init audio
	SDL_AudioSpec audioSpec;
	audioSpec.freq     = 44100;
	audioSpec.format   = AUDIO_S16;
	audioSpec.channels = 2;
	audioSpec.samples  = 512;
	audioSpec.callback = audioCallback;


	SDL_OpenAudio(&audioSpec, NULL);
	SDL_PauseAudio(0); // start audio

	SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
	RenderingContext ctx(screen);

	// load image
	SDL_Surface* bmp = SDL_LoadBMP("mario.bmp");
	if (!bmp) {
		printf("Unable to load bitmap: %s\n", SDL_GetError());
		return 1;
	}

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
				if (event.key.keysym.sym == SDLK_SPACE) amp = amp == 0 ? 255 : 0;
				break;
			}
		}

		// SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0xCC, 0xEE, 0xDD)); // clear screen
		ctx.clear();
		ctx.drawImage(bmp, 32, 16, 16, 16, 200, 200);
		SDL_Flip(screen); // update the screen

		SDL_Delay(100);
	}

	SDL_CloseAudio(); // close audio
	SDL_FreeSurface(bmp); // free loaded bitmap
	printf("Exited cleanly\n");
	return 0;
}
