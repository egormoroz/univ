#include <iostream>
using namespace std;

int f(int x, int n) {
	return x >= 0 ? x : n + x;
}

void shift(int *a, int n, int k) {
	k = k % n;
	if (!k)
		return;
	int j = 0, i = n - k, y = a[i], x;
	a[i] = a[j];
//	cout << j << " -> " << i << endl;
	while (i) {
		j = i;
		i = f(i - k, n);
		x = a[i];
		a[i] = y;
		y = x;
//		cout << j << " -> " << i << endl;
	}
}

void print(int *a, int n) {
	for (int i = 0; i < n; ++i)
		cout << a[i] << ' ';
	cout << endl;
}

int main() {
	int n, k;
	cin >> n >> k;;
	int *a = new int[n];
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	shift(a, n, k);
	print(a, n);
	delete[] a;
}

