#ifndef ASSETS_H
#define ASSETS_H

#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

class Assets {

public:
	SDL_Surface* list[];
	int          length;

	Assets(int);

	void load(char*);

private:
	int size;

}

#endif
