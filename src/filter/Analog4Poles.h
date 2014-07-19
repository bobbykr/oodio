#ifndef ANALOG_4_POLES_H
#define ANALOG_4_POLES_H

class Analog4Poles {

private:
	float pole1;
	float pole2;
	float pole3;
	float pole4;
	float feed1;
	float feed2;

	float resLevel;
	float modMax;
	float modDepth;
	float modScale;
	float levCorrect;

	float* input;

public:
	float reso;
	float dist;
	float freq;
	float out;

	Analog4Poles() {
		pole1 =  0.0;
		pole2 =  0.0;
		pole3 =  0.0;
		pole4 =  0.0;
		feed1 =  0.0;
		feed2 =  0.0;

		resLevel   = 0.0;
		modMax     = 0.0;
		modDepth   = 0.0;
		modScale   = 0.0;
		levCorrect = 0.0;

		reso  =  0.3;
		dist  = -0.5;
		freq  =  0.3;
		out   =  0.0;
	}

	void connectInput(float* in) {
		input = in;
	}

	void tic() {

		float s = freq; // TODO: logarithmic curve

		pole4 = pole3 * s + pole4 * (1 - s); // pole4 = pole4Filter(pole3);
		pole3 = pole2 * s + pole3 * (1 - s); // pole3 = pole3Filter(pole2);
		pole2 = pole1 * s + pole2 * (1 - s); // pole2 = pole2Filter(pole1);
		pole1 = feed1 * s + pole1 * (1 - s); // pole1 = pole1Filter(feed1);

		feed1    = (*input) - resLevel;
		resLevel = feed2 * modMax;
		modMax   = reso + 0.5 * modDepth;
		modDepth = dist * modScale;
		modScale = reso * pole4;
		feed2    = pole4 - 0.5 * levCorrect + 0.695 * feed2;
		levCorrect = (*input) * reso;

		out = pole4;
	}
};

#endif
