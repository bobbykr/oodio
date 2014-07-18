#ifndef FREQ_SEQ_H
#define FREQ_SEQ_H


class FreqSeq {
private:
	int     length;
	double  pos;
	double* steps;
	double  tempo;
	double  inc;

public:
	double out;

	FreqSeq();
	~FreqSeq();
	double tic();
	void   setTempo(double);
};

#endif
