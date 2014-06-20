#include "AmsFont.h"
#include "constants.h"

#define CHAR_SIZE 24;
const int MAX_COLUMN = SCREEN_W / CHAR_SIZE;
const int MAX_LINE   = SCREEN_H / CHAR_SIZE;

AmsFont::AmsFont(char* fileName) {
	font = SDL_LoadBMP(fileName);
	SDL_Surface* surface = SDL_CreateRGBSurface(0, SCREEN_W, SCREEN_H, 32, 0, 0, 0, 0);
	ctx = new RenderingContext(surface);
	_x = 0;
	_y = 0;
}

AmsFont::~AmsFont() {
	delete ctx;
}

SDL_Surface* AmsFont::get() {
	SDL_SetColorKey(ctx->getContext(), SDL_SRCCOLORKEY, SDL_MapRGB(ctx->getContext()->format, 0, 0, 0));
	return ctx->getContext();
};

void AmsFont::locate(int x, int y) {
	_x = x;
	_y = y;
}

void AmsFont::print(char* text) {
	while (*text) {
		int c = *text;
		int posX = (c % 16) * CHAR_SIZE;
		int posY = (c / 16) * CHAR_SIZE;

		// TODO
		// SDL_SetColorKey(font, SDL_SRCCOLORKEY, SDL_MapRGB(font->format, 0, 0, 0));
		ctx->drawImage(font, posX, posY, CHAR_SIZE, CHAR_SIZE, _x * CHAR_SIZE, _y * CHAR_SIZE);

		text++;
		if (++_x >= MAX_COLUMN) {
			_x = 0;
			if (++_y > MAX_LINE) {
				_y--;
				scroll(1);
			}
		}
	}
}

void AmsFont::chr(int) {
	// TODO
}

void AmsFont::scroll(int) {
	// TODO
}
