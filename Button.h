#ifndef BUTTON_H
#define BUTTON_H

#include "AmsFont.h"

class Button {

public:

	Button(int, int, char*);

	void clic(int, int);
	void draw(AmsFont*);
	void onClic(void (*)());

private:
	char*    name;
	int      x;
	int      y;
	int      width;
	int      pen;
	void    (*cb) ();
};

#endif
