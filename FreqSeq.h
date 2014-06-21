#ifndef FREQ_SEQ_H
#define FREQ_SEQ_H


class FreqSeq {

public:

	FreqSeq();
	float tic();

	float out;
	float tempo;

private:

	float pos;
	float steps[8];
};

#endif
