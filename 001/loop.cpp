#include <iostream>
using namespace std;

int main() {
	int a, b;
	//a <= b
	cin >> a >> b;
	int m = a * b, r = b % a;
	while (r) {
		b = a;
		a = r;
		r = b % a;
	}
	cout << "gcd: " << a << '\n';
	cout << "lcm: " << (m / a) << endl;
}

