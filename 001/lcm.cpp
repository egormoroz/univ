#include <iostream>
using namespace std;

int gcd(int a, int b) {
	int r = b % a;
	return r ? gcd(r, a) : a;
}

int lcm(int a, int b) {
	//gcd(a, b) * lcm(a, b) == a * b
	return a * b / gcd(a, b);
}

int main() {
	int a, b;
	cin >> a >> b;
	cout << lcm(a, b) << endl;
}

