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

	void clear();
	void update();
	void drawImage(SDL_Surface*, int, int);
	void drawImage(SDL_Surface*, int, int, int, int, int, int);

private:

	SDL_Surface* context;
	SDL_Rect     clip;
	SDL_Rect     translate;
	Uint32       backgroundColor;
};

#endif
