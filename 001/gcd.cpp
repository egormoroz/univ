//Nothing to see here
#ifdef TEST_GCD
#include <iostream>
using namespace std;

int gcd(int a, int b) {
	int r = b % a;
	return r ? gcd(r, a) : a;
}

int stupid_gcd(int a, int b) {
	for (int i = a; i > 0; --i) {
		if (!(a % i | b % i))
			return i;
	}
	cerr << "reached unreachable code" << endl;
	abort();
	//unreachable b = a (mod 1), which is 0
}

int main() {
	ios::sync_with_stdio(false);
	const int N = 1000;
	for (int a = 1; a <= N; ++a)
		for (int b = a + 1; b <= N; ++b)
		{
			if (gcd(a, b) != stupid_gcd(a, b))
				cout << "failed for (" << a << ", " << b << ")\n";
		}
	cout << "done" << endl;
}
#endif

