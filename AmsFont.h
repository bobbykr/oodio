#ifndef AMS_FONT_H
#define AMS_FONT_H

#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include "RenderingContext.h"

class AmsFont {

public:
	AmsFont(char*);
	~AmsFont();

	SDL_Surface* get();
	void locate(int, int);
	void print(char*);
	void chr(int);
	void scroll(int);

	RenderingContext* ctx;

private:
	SDL_Surface*     font;
	int              _x;
	int              _y;
};

#endif
