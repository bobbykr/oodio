#ifndef DECAY_ENVELOPE_H
#define DECAY_ENVELOPE_H

class DecayEnvelope {

private:
	int    t;
	double a;
	double b;
	double releaseTime;
	double curvature;
	bool   stopped;

	void update() {
		// FIXME: if parameters changes while envelope playing,
		//        there will be an audio glich.
		//        process should only use previous output value, not t.
		a = (2 - 4 * curvature) / (double)(releaseTime * releaseTime);
		b = (4 * curvature - 3) / (double)releaseTime;
	};

public:
	double out;

	DecayEnvelope() {
		releaseTime = 500; // TODO: release time in ms, not in tick
		curvature = 0.3;
		stopped = true;
		t = 0;
		update();
	};

	void trigger() {
		stopped = false;
		t = 0;
	};

    double tic() {
    	if (stopped) return 0;
    	if (t++ > releaseTime) {
    		stopped = true;
    		out = 0;
    	}
    	out = a * (double)(t * t) + b * (double)t + 1;
		return out;
	};

	void setCurvature(double c) {
		curvature = c;
		update();
	};

	void setReleaseTime(int r) {
		releaseTime = r;
		update();
	};
};

#endif