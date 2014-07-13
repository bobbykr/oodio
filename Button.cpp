#include "Button.h"
#include "constants.h"


Button::Button(int _x, int _y, char* _name) {
	x     = _x;
	y     = _y;
	name  = _name;
	cb    = NULL;
	width = 0;
	color = 24;
	while (*_name++) width++;
}

void Button::clic(int clicX, int clicY) {
	if (cb == NULL) return;
	clicX = clicX / (8 * PIXEL);
	clicY = clicY / (8 * PIXEL);

	if (clicX >= x && clicX < x + width && clicY >= y && clicY < y + 1) {
		cb();
	}
}

void Button::draw(AmsFont* ctx) {
	ctx->locate(x, y);
	ctx->paper(color);
	ctx->pen(1);
	ctx->print(name);
}

void Button::onClic(void (*callback) ()) {
	cb = callback;
}