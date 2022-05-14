#include <iostream>
#include "FlipFlop.h"

using std::cout;
using std::endl;

int main() {
	DFF dff0 = DFF();
	DFF dff1 = DFF();
	DFF dff2 = DFF();
	DFF dff3 = DFF();

	bool bit0, bit1, bit2, bit3;
	bool clock = true;

	bit0 = dff0.LchOutput(true);
	bit1 = dff1.LchOutput(true);
	bit2 = dff2.LchOutput(true);
	bit3 = dff3.LchOutput(true);
	cout << bit3 << bit2 << bit1 << bit0 << endl;

	for (int i = 0; i < 20; i++) {
		bit0 = dff0.DIO(bit0, clock, true);
		bit1 = dff1.DIO(bit1, dff0.LchOutput(), true);
		bit2 = dff2.DIO(bit2, dff1.LchOutput(), true);
		bit3 = dff3.DIO(bit3, dff2.LchOutput(), true);

		dff0.ClockFall();

		cout << "Loop " << i << endl;
		cout << bit3 << bit2 << bit1 << bit0 << endl;
		cout << "====" << endl;
	}

	return 0;
}