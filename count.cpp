#include <iostream>
#include "FlipFlop.h"

using std::cout;
using std::endl;

int main() {
	TFF tff0 = TFF();
	TFF tff1 = TFF();
	TFF tff2 = TFF();
	TFF tff3 = TFF();

	bool bit0, bit1, bit2, bit3;
	bool clock=true;

	bit0 = tff0.LchOutput();
	bit1 = tff1.LchOutput();
	bit2 = tff2.LchOutput();
	bit3 = tff3.LchOutput();

	for (int i = 0; i < 20; i++) {
		bit3 = tff3.TIO((bit0 & bit1 & bit2), clock);
		bit2 = tff2.TIO((bit0 & bit1), clock);
		bit1 = tff1.TIO(bit0, clock);
		bit0 = tff0.TIO(1, clock);
		
		cout << "Loop " << i << endl;
		cout << bit3 << bit2 << bit1 << bit0 << endl;
		cout << "====" << endl;
	}

	return 0;
}