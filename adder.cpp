#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class FullAdder {
private:
	bool A[4], B[4];
public:
	FullAdder(bool a[4], bool b[4]) {
		for (int i = 0; i < 4; i++) {
			A[i] = a[i];
			B[i] = b[i];
		}
	}
	bool bitAdder(bool a, bool b, bool c,bool sc_Mode) {
		bool temp1, temp2, temp3;
		bool sum,carry;
		temp1 = a ^ b;
		temp2 = a & b;
		temp3 = temp1 & c;

		sum = temp1 ^ c;	//sum
		carry = temp3 | temp2;	//carry

		return (sc_Mode == true ? sum : carry);
	}
	void Compute(bool Mode) {  // 0: add, 1: sub
		bool sum[4], carry[4];
		int result;

		for (int i = 0; i < 4; i++) B[i] ^= Mode;

		sum[0] = bitAdder(A[0], B[0], Mode,1);
		carry[0] = bitAdder(A[0], B[0], Mode,0);

		for (int i = 0; i < 3; i++) {
			sum[i + 1] = bitAdder(A[i + 1], B[i + 1], carry[i],1);
			carry[i + 1] = bitAdder(A[i + 1], B[i + 1], carry[i],0);
		}
		cout << (Mode == false ? "µ¡¼À°ª : " : "»¬¼À°ª : ") << carry[3] << sum[3] << sum[2] << sum[1] << sum[0] << endl;
		if (Mode == false) {
			result = (carry[3] << 4) | (sum[3] << 3) | (sum[2] << 2) | (sum[1] << 1) | sum[0];
		}
		else if (carry[3] == true) {
			result = (sum[3] << 3) | (sum[2] << 2) | (sum[1] << 1) | sum[0];
		}
		else {
			result = ((sum[3] ^ 1) << 3) | ((sum[2] ^ 1) << 2) | ((sum[1] ^ 1) << 1) | (sum[0]) ^ 1;
			result=-result-1;
		}
		cout << "°á°ú(DEC): " << result << endl;
	
	}
};

int main() {
	bool a[4], b[4];
	int temp;


	cout << "unsigned A ÀÔ·Â: ";
	for (int i = 3; i >= 0; i--) cin >> a[i];
	temp = (a[3] << 3) | (a[2] << 2) | (a[1] << 1) | a[0];
	cout << "ÀÔ·Â°ª(DEC): " << temp << endl;
	cout << "unsigned B ÀÔ·Â: ";
	for (int i = 3; i >= 0; i--) cin >> b[i];
	temp = (b[3] << 3) | (b[2] << 2) | (b[1] << 1) | b[0];
	cout << "ÀÔ·Â°ª(DEC): " << temp << endl;
	cout << "===============================" << endl;

	FullAdder fulladder = FullAdder(a, b);
	fulladder.Compute(0);
	fulladder.Compute(1);

	return 0;
}