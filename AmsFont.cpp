#include "AmsFont.h"
#include "constants.h"

const int CHAR_SIZE  = 24;
const int MAX_COLUMN = SCREEN_W / CHAR_SIZE;
const int MAX_LINE   = SCREEN_H / CHAR_SIZE;


AmsFont::AmsFont(char* fileName) {
	font = SDL_LoadBMP(fileName);
	SDL_Surface* surface = SDL_CreateRGBSurface(0, SCREEN_W, SCREEN_H, 32, 0, 0, 0, 0);
	ctx = new RenderingContext(surface);
	_x = 0;
	_y = 0;
	_clearRect = SDL_CreateRGBSurface(SDL_HWSURFACE, CHAR_SIZE, CHAR_SIZE, 32, 0, 0, 0, 0);
	_paper = {0, 0, 0};
}

AmsFont::~AmsFont() {
	delete ctx;
	SDL_FreeSurface(_clearRect);
}

SDL_Surface* AmsFont::get() {
	SDL_SetColorKey(ctx->getContext(), SDL_SRCCOLORKEY, SDL_MapRGB(ctx->getContext()->format, 0, 0, 0));
	return ctx->getContext();
}

void AmsFont::paper(int code) {
	if (code == -1 || code > 27) {
		_paper = {0, 0, 0};
		return;
	}

	int r = (code / 3) % 3;
	int g = (code / 9);
	int b = code % 3;

	if (r == 0 && g == 0 && b == 0) b = 1; // no transparency
	_paper = {r, g, b};
}

void AmsFont::locate(int x, int y) {
	_x = x;
	_y = y;
}

void AmsFont::print(char* text) {
	while (*text) {
		int c = *text;
		text++;

		if (c == '\n') {
			_x = 0;
			_y++;
			continue;
		}

		int sourceX = (c % 16) * CHAR_SIZE;
		int sourceY = (c / 16) * CHAR_SIZE;
		int destX = _x * CHAR_SIZE;
		int destY = _y * CHAR_SIZE;

		// clear character background
		_clearPos.x = destX;
		_clearPos.y = destY;
		// paper color
		SDL_FillRect(_clearRect, NULL, SDL_MapRGB(ctx->getContext()->format, _paper[0], _paper[1], _paper[2]));
		SDL_BlitSurface(_clearRect, NULL, ctx->getContext(), &_clearPos);
		// draw character
		ctx->drawImage(font, sourceX, sourceY, CHAR_SIZE, CHAR_SIZE, destX, destY);
		
		if (++_x >= MAX_COLUMN) {
			_x = 0;
			if (++_y > MAX_LINE) {
				_y--;
				scroll(1);
			}
		}
	}
}

void AmsFont::scroll(int) {
	// save current 
	// TODO
}
