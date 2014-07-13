#ifndef SLIDER_H
#define SLIDER_H

#include "AmsFont.h"

class Slider {

public:

	Slider(int, int, int, double, double);

	void clic(int, int);
	void move(int, int);
	void unclic(int, int);

	void draw(AmsFont*);
	void onChange(void (*)(double));

private:
	bool     tapped;
	double   value;
	double   min;
	double   max;
	int      x;
	int      y;
	int      width;
	void    (*cb) (double);
};

#endif
