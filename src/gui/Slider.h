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
	void onChange(void (*)(float)); // bind to a function
	void onChange(float*);          // bind to a variable

private:
	bool     tapped;
	float    value;
	float    min;
	float    max;
	int      x;
	int      y;
	int      width;

	void     (*cb) (float); // onChange callback
	float*   bind;          // onChange binded variable
};

#endif
