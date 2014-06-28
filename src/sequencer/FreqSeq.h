#ifndef FREQ_SEQ_H
#define FREQ_SEQ_H


class FreqSeq {
private:
	int    length;
	double  pos;
	double* steps;

public:
	double out;
	double tempo;

	FreqSeq();
	~FreqSeq();
	double tic();
};

#endif
