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
	void backgroundColor(int, int, int);
	void drawImage(SDL_Surface*, int, int);
	void drawImage(SDL_Surface*, int, int, int, int, int, int);

	SDL_Surface* getContext();

private:

	SDL_Surface* context;
	SDL_Rect     clip;
	SDL_Rect     translate;
	uint32_t     bgColor;
};

#endif
