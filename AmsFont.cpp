#include "AmsFont.h"
#include "constants.h"


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
	return ctx->getContext();
};

void AmsFont::locate(int x, int y) {
	_x = x;
	_y = y;
}

void AmsFont::print(char* text) {
	while (*text) {
		int c = *text;

		// TODO
		SDL_SetColorKey(font, SDL_SRCCOLORKEY, SDL_MapRGB(font->format, 0, 0, 0));
		ctx->drawImage(font, 24, 24, 24, 24, _x * 24, _y * 24);

		text++;
		_x++;
		if (_x > 32) {
			_x = 0;
			_y++;
		}
	}
}

void AmsFont::chr(int) {
	// TODO
}

void AmsFont::scroll(int) {
	// TODO
}
