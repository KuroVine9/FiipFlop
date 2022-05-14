#ifndef FlipFlop_H
#define FlipFlop_H

#include <iostream>

using std::cout;
using std::endl;

class Latch {
private:
	bool S, R;
	bool Q, Q_;

	void Compute() {
		Q = !(R | Q_);
		Q_ = !(S | Q);
		Q = !(R | Q_);
	}
public:
	Latch() {
		S = false;
		R = false;
		Q = false;
		Q_ = !Q;
	}

	void LchInput(bool set, bool reset) {
		S = set;
		R = reset;
		Compute();
	}

	bool LchOutput(bool Mode = false) {	//0: Q, 1: Q_
		return (Mode == false ? Q : Q_);
	}
	bool LchIO(bool set, bool reset, bool Mode = false) {
		LchInput(set, reset);
		LchOutput(Mode);
	}
	void PrintStat() {
		cout << "============" << endl;
		cout << "S: " << S << endl;
		cout << "R: " << R << endl;
		cout << "Q: " << Q << endl;
		cout << "Q_: " << Q_ << endl;
		cout << "============" << endl;
	}

};

class JKFF : public Latch {
private:
	bool J, K;
	bool CP;
	bool CPCHK;
public:
	JKFF() {
		J = false;
		K = false;
		CP = false;
		CPCHK = CP;
	}
	void ClockFall() {
		CP = false;
		CPCHK = CP;
	}
	void JKInput(bool j, bool k, bool cp) {
		J = j;
		K = k;
		CP = cp;
		LchInput(((CPCHK == false && CP == true ? true : false) & J & LchOutput(true)), ((CPCHK == false && CP == true ? true : false) & K & LchOutput(false)));
		CPCHK = cp;
	}
	bool JKIO(bool j, bool k, bool cp, bool Mode = false) {
		JKInput(j, k, cp);
		return (LchOutput(Mode));
	}
	void PrintStat() {
		cout << "============" << endl;
		cout << "J: " << J << endl;
		cout << "K: " << K << endl;
		cout << "CP: " << CP << endl;
		cout << "CPCHK: " << CPCHK << endl;
		cout << "Q: " << LchOutput(false) << endl;
		cout << "Q_: " << LchOutput(true) << endl;
		cout << "============" << endl;
	}
};

class TFF : public Latch {
private:
	bool T;
	bool CP;
	bool CPCHK;
public:	
	
	TFF() {
		T = false;
		CP = false;
		CPCHK = CP;
	}
	void ClockFall() {
		CP = false;
		CPCHK = CP;
	}
	void TInput(bool t, bool cp) {
		T = t;
		CP = cp;
		LchInput(((CPCHK == false && CP == true ? true : false) & T & LchOutput(true)), ((CPCHK == false && CP == true ? true : false) & T & LchOutput(false)));
		CPCHK = cp;
	}
	bool TIO(bool t, bool cp, bool Mode = false) {
		TInput(t, cp);
		return (LchOutput(Mode));
	}
	void PrintStat() {
		cout << "============" << endl;
		cout << "T: " << T << endl;
		cout << "CP: " << CP << endl;
		cout << "CPCHK: " << CPCHK << endl;
		cout << "Q: " << LchOutput(false) << endl;
		cout << "Q_: " << LchOutput(true) << endl;
		cout << "============" << endl;
	}
};

class DFF : public Latch {
private:
	bool D;
	bool CP;
	bool CPCHK;
public:
	DFF() {
		D = false;
		CP = false;
		CPCHK = CP;
	}
	void ClockFall() {
		CP = false;
		CPCHK = CP;
	}
	void DInput(bool d, bool cp) {
		D = d;
		CP = cp;
		LchInput(((CPCHK == false && CP == true ? true : false) & D), ((CPCHK == false && CP == true ? true : false) & (!D)));
		CPCHK = cp;
	}
	bool DIO(bool d, bool cp, bool Mode = false) {
		DInput(d, cp);
		return (LchOutput(Mode));
	}
	void PrintStat() {
		cout << "============" << endl;
		cout << "D: " << D << endl;
		cout << "CP: " << CP << endl;
		cout << "CPCHK: " << CPCHK << endl;
		cout << "Q: " << LchOutput(false) << endl;
		cout << "Q_: " << LchOutput(true) << endl;
		cout << "============" << endl;
	}
};


#endif
