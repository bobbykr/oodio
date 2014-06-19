#include "Assets.h"
#include <stdlib.h>

Assets::Assets(int s) {
	length = 0;
	size = s;
	list = (SDL_Surface*) malloc(s);
}

void Assets::load(char* name) {
	if (length >= size) throw 0;
	list[length++] = SDL_LoadBMP(name);
}
