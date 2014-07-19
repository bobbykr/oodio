#ifndef DECAY_ENVELOPE_H
#define DECAY_ENVELOPE_H

class DecayEnvelope {

private:
	int    t;
	float a;
	float b;
	float releaseTime;
	float curvature;
	bool   stopped;

	void update() {
		// FIXME: if parameters changes while envelope playing,
		//        there will be an audio glich.
		//        process should only use previous output value, not t.
		a = (2 - 4 * curvature) / (float)(releaseTime * releaseTime);
		b = (4 * curvature - 3) / (float)releaseTime;
	};

public:
	float out;

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

    float tic() {
		if (stopped) return 0;
		if (t++ > releaseTime) {
			stopped = true;
			out = 0;
		}
		out = a * (float)(t * t) + b * (float)t + 1;
		return out;
	};

	float tic(float trig) {
		if (trig > 0.8) {
			stopped = false;
			t = 0;
		}
		if (stopped) return 0;
		if (t++ > releaseTime) {
			stopped = true;
			out = 0;
		}
		out = a * (float)(t * t) + b * (float)t + 1;
		return out;
	};

	void setCurvature(float c) {
		curvature = c;
		update();
	};

	void setReleaseTime(int r) {
		releaseTime = r;
		update();
	};
};

#endif