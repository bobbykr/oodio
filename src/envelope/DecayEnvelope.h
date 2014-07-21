#ifndef DECAY_ENVELOPE_H
#define DECAY_ENVELOPE_H

const float _decEnvSmooth = 0.02;
const float _decEnvSmoothInv = 1 - _decEnvSmooth;

class DecayEnvelope {

private:
	float* trig;
	int    t;
	float  a;
	float  b;
	float  raw;
	float  releaseTime;
	float  curvature;
	bool   stopped;

	void update() {
		// FIXME: if parameters changes while envelope playing,
		//        there will be an audio glich.
		//        process should only use previous output value, not t.
		a = (2 - 4 * curvature) / (float)(releaseTime * releaseTime);
		b = (4 * curvature - 3) / (float)releaseTime;
	}

public:
	float out;

	DecayEnvelope() {
		releaseTime = 500; // TODO: release time in ms, not in tick
		curvature = 0.3;
		stopped = true;
		t = 0;
		out = 0.0;
		raw = 0.0;
		update();
	}

	void connect(float* input) {
		trig = input;
	}

	void tic() {
		if (*trig > 0.8) {
			stopped = false;
			t = 0;
		}
		if (stopped) return;
		if (t++ > releaseTime) {
			stopped = true;
			out = 0;
		}
		raw = a * (float)(t * t) + b * (float)t + 1;

		// built in smoothing filter
		out = raw * _decEnvSmooth + out * _decEnvSmoothInv;
	}

	void setCurvature(float c) {
		curvature = c;
		update();
	}

	void setReleaseTime(int r) {
		releaseTime = r;
		update();
	}
};

#endif
