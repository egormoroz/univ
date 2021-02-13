#include <iostream>
using namespace std;

int main() {
	int n, k;
	cin >> n >> k;;
	int *a = new int[n];
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	for (int i = 0; i < n; ++i)
		cout << a[(i + k) % n] << ' ';
	cout << endl;
	delete[] a;
}
