#include "Slider.h"
#include "constants.h"


Slider::Slider(int _x, int _y, int _width, double _min, double _max) {
	if (min == max) throw 0;
	x      = _x;
	y      = _y;
	width  = _width;
	min    = _min;
	max    = _max;
	value  = _min + (_max - _min) * 0.5;

	cb     = NULL;
	tapped = false;
}

void Slider::clic(int mouseX, int mouseY) {
	mouseX = mouseX / (8 * PIXEL);
	mouseY = mouseY / (8 * PIXEL);
	if (mouseX >= x && mouseX < x + width && mouseY >= y && mouseY < y + 1) {
		tapped = true;
	}
}

void Slider::move(int mouseX, int mouseY) {
	if (!tapped) return;
	double v = min + (max - min) * ((double)(mouseX - x * (8 * PIXEL)) / (double)((width - 1) * (8 * PIXEL)));
	if (v < min) v = min;
	if (v > max) v = max;
	value = v;
}

void Slider::unclic(int mouseX, int mouseY) {
	if (!tapped) return;
	tapped = false;
	if (cb == NULL) return;
	cb(value);
}

void Slider::draw(AmsFont* ctx) {
	ctx->locate(x, y);
	ctx->paper(4);


	int pos = (int) ((double) (width - 1) * ((value - min) / (max - min)));
	for (int i = 0; i < width; i++) {
		if (i == pos) {
			ctx->paper(24);
			ctx->print(" ");
			ctx->paper(4);
		} else {
			ctx->print(" ");
		}
	}
}

void Slider::onChange(void (*callback) (double)) {
	cb = callback;
}