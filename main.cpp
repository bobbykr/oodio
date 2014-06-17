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

uint8_t sawtooth = 0;

void audioCallback(void* udata, uint8_t* stream, int len) {
	for (; len; len--) {
		*stream++ = sawtooth++ >> 5;
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
	audioSpec.channels = 1;
	audioSpec.samples  = 512;
	audioSpec.callback = audioCallback;

	if (SDL_OpenAudio(&audioSpec, NULL) < 0) {
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		return(-1);
	};

	// start audio
	SDL_PauseAudio(0);

	// create a new window
	SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (!screen) {
		printf("Unable to set 640x480 video: %s\n", SDL_GetError());
		return 1;
	}

	// load image
	SDL_Surface* bmp = SDL_LoadBMP("mario.bmp");
	if (!bmp) {
		printf("Unable to load bitmap: %s\n", SDL_GetError());
		return 1;
	}

	// centre the bitmap on screen
	SDL_Rect dstrect;
	dstrect.x = (screen->w - bmp->w) / 2;
	dstrect.y = (screen->h - bmp->h) / 2;

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
				break;
			}
		}

		SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0xCC, 0xEE, 0xDD)); // clear screen
		SDL_SetColorKey(bmp, SDL_SRCCOLORKEY, SDL_MapRGB(bmp->format, 255, 0, 0));
        /* On blitte l'image maintenant transparente sur le fond : */
		SDL_BlitSurface(bmp, NULL, screen, &dstrect); // draw bitmap
		SDL_Flip(screen); // update the screen

		SDL_Delay(100);
	}


	SDL_CloseAudio(); // close audio
	SDL_FreeSurface(bmp); // free loaded bitmap
	printf("Exited cleanly\n");
	return 0;
}
