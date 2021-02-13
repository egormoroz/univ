#include <iostream>
using namespace std;

void shift(int* src, int* dst, int n, int k) {
	k = k % n;
	if (!k)
		return;
	for (int i = 0; i < n; ++i) {
		int j = i - k;
		if (j < 0)
			j = n + j;
		dst[j] = src[i];
	}
}

int main() {
	int n, k;
	cin >> n >> k;
	int* src = new int[n];
	int* dst = new int[n];

	for (int i = 0; i < n; ++i)
		cin >> src[i];
	shift(src, dst, n, k);
	
	for (int i = 0; i < n; ++i)
		cout << dst[i] << ' ';
	cout << endl;

	delete[] dst;
	delete[] src;
}
