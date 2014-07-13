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

	SDL_Surface* getImage();
	void paper(int);
	void pen(int);
	void locate(int, int);
	void print(char);
	void print(char*);
	void printNumber(int);
	void scroll(int);

	RenderingContext* ctx;

private:
	SDL_Surface*      font;
	int               _x;
	int               _y;
	SDL_Surface*      _clearRect;
	SDL_Rect          _clearPos;
	int               _paper[3];
	RenderingContext* _pen;

};

#endif
