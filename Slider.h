#ifndef SLIDER_H
#define SLIDER_H

#include "AmsFont.h"

class Slider {

public:

	Slider(int, int, int, float, float);

	void clic(int, int);
	void move(int, int);
	void unclic(int, int);

	void draw(AmsFont*);
	void onChange(void (*)(float));

private:
	bool     tapped;
	float    value;
	float    min;
	float    max;
	int      x;
	int      y;
	int      width;
	void    (*cb) (float);
};

#endif
