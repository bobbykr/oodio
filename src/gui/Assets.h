#ifndef ASSETS_H
#define ASSETS_H

#include <SDL.h>

class Assets {

public:
	SDL_Surface* list[];
	int          length;

	Assets(int);

	void load(char*);

private:
	int size;

};

#endif
