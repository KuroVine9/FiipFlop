#include <iostream>
#include "FlipFlop.h"

using std::cout;
using std::endl;

int main() {
	DFF dff0 = DFF();
	DFF dff1 = DFF();
	DFF dff2 = DFF();
	DFF dff3 = DFF();

	bool bit0, bit1, bit2, bit3, temp;
	bool clock = true;

	bit0 = dff0.LchOutput();
	bit1 = dff1.LchOutput();
	bit2 = dff2.LchOutput();
	bit3 = dff3.LchOutput();
	temp = bit3;

	for (int i = 0; i < 20; i++) {
		bit3 = dff3.DIO(bit2, clock);
		bit2 = dff2.DIO(bit1, clock);
		bit1 = dff1.DIO(bit0, clock);
		bit0 = dff0.DIO((!temp), clock);
		temp = bit3;

		dff3.ClockFall();
		dff2.ClockFall();
		dff1.ClockFall();
		dff0.ClockFall();

		cout << "Loop " << i << endl;
		cout << bit0 << bit1 << bit2 << bit3 << endl;
		cout << "====" << endl;
	}

	return 0;
}