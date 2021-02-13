#include <iostream>
using namespace std;

template<int N>
struct Factorial {
	static const int VALUE = Factorial<N - 1>::VALUE * N;
};

template<>
struct Factorial<0> {
	static const int VALUE = 1;
};

constexpr int factorial(int n) noexcept {
	return n > 1 ? factorial(n - 1) * n : 1;
}

int main() {
	const int N = factorial(3);
	const int M = Factorial<N>::VALUE;
	
	cout << M << endl;
}

