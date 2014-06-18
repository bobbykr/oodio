#ifndef RENDERING_CONTEXT_H
#define RENDERING_CONTEXT_H

#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

class RenderingContext {

public:

	RenderingContext(SDL_Surface*);

	void drawImage(SDL_Surface*, int, int);
	void drawImage(SDL_Surface*, int, int, int, int, int, int);

private:

	SDL_Surface* context;

};

#endif
