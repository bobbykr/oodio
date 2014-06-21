#ifndef FREQ_SEQ_H
#define FREQ_SEQ_H


class FreqSeq {

public:

	FreqSeq();
	~FreqSeq();
	float tic();

	float out;
	float tempo;

private:
	int    length;
	float  pos;
	float* steps;
};

#endif
