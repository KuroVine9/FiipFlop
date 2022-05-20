#include <iostream>
#include "FlipFlop.h"

using std::cout;
using std::endl;
using std::cin;

bool MUX_4_1(bool s0, bool s1, bool d0, bool d1, bool d2, bool d3) {
	return (!s0 & !s1&d0) | (s0 & !s1&d1) | (!s0&s1&d2) | (s0&s1&d3);
}


int main() {
	bool S0, S1;
	bool I0, I1, I2, I3;
	bool RSIPT,LSIPT;
	bool Out0, Out1, Out2, Out3;
	bool temp0, temp1, temp2, temp3;
	bool clr;
	int sel;

	DFF dff0, dff1, dff2, dff3;

	I0 = false;
	I1 = false;
	I2 = false;
	I3 = false;

	RSIPT = false;
	LSIPT = false;

	S0 = false;
	S1 = false;

	temp0 = dff0.LchOutput();
	temp1 = dff1.LchOutput();
	temp2 = dff2.LchOutput();
	temp3 = dff3.LchOutput();

	while (true) {
		cout << "모드 선택" << endl;
		cout << "0. 우측 시프트 직렬 입력\n1. 좌측 시프트 직렬 입력\n2. 병렬 입력(LOAD)\n3. 우측 시프트 출력\n4. 좌측 시프트 출력\n5. 불변 상태\n6. 클리어 비트 조작(Active-Low)" << endl;
		cout << "\t>> ";
		cin >> sel;
		cout << "======" << endl;

		switch (sel) {
		case 0:
			cout << "Input bit(1bit)\n\t>>";
			cin >> RSIPT;
		case 3:
			S0 = true;
			S1 = false;
			break;

		case 1:
			cout << "Input bit(1bit)\n\t>>";
			cin >> LSIPT;
		case 4:
			S0 = false;
			S1 = true;
			break;

		case 2:
			S0 = true;
			S1 = true;
			cout << "Input bit(4bit) MSB--LSB\n\t>>";
			cin >> I0;
			cin >> I1;
			cin >> I2;
			cin >> I3;
			break;
		case 5:
			S0 = false;
			S1 = false;
			break;
		case 6:
			cout << "Input CLR bit(1bit)\n\t>>";
			cin >> clr;
			dff0.Clear(clr);
			dff1.Clear(clr);
			dff2.Clear(clr);
			dff3.Clear(clr);
			break;
		default:
			cout << "프로그램을 종료합니다..." << endl;
			return 0;
			break;
		}

		Out0 = dff0.DIO(MUX_4_1(S0, S1, temp0, RSIPT, temp1, I0), true);
		Out1 = dff1.DIO(MUX_4_1(S0, S1, temp1, temp0, temp2, I1), true);
		Out2 = dff2.DIO(MUX_4_1(S0, S1, temp2, temp1, temp3, I2), true);
		Out3 = dff3.DIO(MUX_4_1(S0, S1, temp3, temp2, LSIPT, I3), true);

		temp0 = dff0.LchOutput();
		temp1 = dff1.LchOutput();
		temp2 = dff2.LchOutput();
		temp3 = dff3.LchOutput();

		dff0.ClockFall();
		dff1.ClockFall();
		dff2.ClockFall();
		dff3.ClockFall();

		cout << Out0 << Out1 << Out2 << Out3 << endl;
		cout << "============" << endl;
	}

	return 0;
}