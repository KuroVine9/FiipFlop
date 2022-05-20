#include <iostream>
#include "FlipFlop.h"

using std::cout;
using std::endl;

int main() {
	JKFF jkff0, jkff1, jkff2;
	bool bit0, bit1, bit2, temp0, temp1, temp2;

	bit0 = jkff0.LchOutput();
	bit1 = jkff1.LchOutput();
	bit2 = jkff2.LchOutput();

	temp0 = bit0;
	temp1 = bit1;
	temp2 = bit2;

	for (int i = 0; i < 20; i++) {
		bit2 = jkff2.JKIO((jkff1.LchOutput()&jkff0.LchOutput(true)), (jkff1.LchOutput(true)&jkff0.LchOutput(true)), true);
		bit1 = jkff1.JKIO((!temp2&jkff0.LchOutput()), (temp2&jkff0.LchOutput()), true);
		bit0 = jkff0.JKIO(!(temp2^temp1), (temp2^temp1), true);

		temp0 = bit0;
		temp1 = bit1;
		temp2 = bit2;

		jkff0.ClockFall();
		jkff1.ClockFall();
		jkff2.ClockFall();

		cout << "Loop " << i << endl;
		cout << bit2 << bit1 << bit0 << endl;
		cout << "====" << endl;
	}
	return 0;
}