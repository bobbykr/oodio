#ifndef FREQ_SEQ_H
#define FREQ_SEQ_H


class FreqSeq {
private:
	int    length;
	float  pos;
	float* steps;

public:
	float out;
	float tempo;

	FreqSeq();
	~FreqSeq();
	float tic();
};

#endif
