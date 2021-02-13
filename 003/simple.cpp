#include <iostream>
using namespace std;

template<typename T>
T find_min(const T *a, int n) {
	T m = a[0];
	for (int i = 1; i < n; ++i)
		if (a[i] < m)
			m = a[i];
	return m;
}

int main() {
	int *i = new int[5]{1, -5, 2, 3, 4};
	float *f = new float[5]{1., -5.2, -5.23, 4, 5};
	double *d = new double[5]{1., -5.2, -5.23, 4, 5};
	cout << find_min(i, 5) << endl;
	cout << find_min(f, 5) << endl;
	cout << find_min(d, 5) << endl;
	delete[] d;
	delete[] f;
	delete[] i;
}

