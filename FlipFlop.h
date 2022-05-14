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
		if ((Q == true && Q_ == false && ((S | R) == false)) || S == true) {
			Q_ = !(S | Q);
			Q = !(R | Q_);
		}
		else if ((Q == false && Q_ == true && ((S | R) == false)) || R == true) {
			Q = !(R | Q_);
			Q_ = !(S | Q);
		}
		else {
			cout << "Err" << endl;
		}

		if (Q == Q_) {
			cout << "Err" << endl;
		}
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
public:
	JKFF() {
		J = false;
		K = false;
		CP = false;
	}
	void JKInput(bool j, bool k, bool cp) {
		J = j;
		K = k;
		CP = cp;
		LchInput((CP & J & LchOutput(true)), (CP & K & LchOutput(false)));
	}
	bool JKIO(bool j, bool k, bool cp, bool Mode = false) {
		J = j;
		K = k;
		CP = cp;
		LchInput((CP & J & LchOutput(true)), (CP & K & LchOutput(false)));
		return (LchOutput(Mode));
	}
	void PrintStat() {
		cout << "============" << endl;
		cout << "J: " << J << endl;
		cout << "K: " << K << endl;
		cout << "CP: " << CP << endl;
		cout << "Q: " << LchOutput(false) << endl;
		cout << "Q_: " << LchOutput(true) << endl;
		cout << "============" << endl;
	}
};

class TFF : public Latch {
private:
	bool T;
	bool CP;
public:
	TFF() {
		T = false;
	}
	void TInput(bool t, bool cp) {
		T = t;
		CP = cp;
		LchInput((CP & T & LchOutput(true)), (CP & T & LchOutput(false)));
	}
	bool TIO(bool t, bool cp, bool Mode = false) {
		T = t;
		CP = cp;
		LchInput((CP & T & LchOutput(true)), (CP & T & LchOutput(false)));
		return (LchOutput(Mode));
	}
	void PrintStat() {
		cout << "============" << endl;
		cout << "T: " << T << endl;
		cout << "CP: " << CP << endl;
		cout << "Q: " << LchOutput(false) << endl;
		cout << "Q_: " << LchOutput(true) << endl;
		cout << "============" << endl;
	}
};

class DFF : public Latch {
private:
	bool D;
	bool CP;
public:
	DFF() {
		D = false;
		CP = false;
	}
	void DInput(bool d, bool cp) {
		D = d;
		CP = cp;
		LchInput((CP & D), (CP & (!D)));
	}
	bool DIO(bool d, bool cp, bool Mode = false) {
		D = d;
		CP = cp;
		LchInput((CP & D), (CP & (!D)));
		return (LchOutput(Mode));
	}
	void PrintStat() {
		cout << "============" << endl;
		cout << "D: " << D << endl;
		cout << "CP: " << CP << endl;
		cout << "Q: " << LchOutput(false) << endl;
		cout << "Q_: " << LchOutput(true) << endl;
		cout << "============" << endl;
	}
};


#endif
