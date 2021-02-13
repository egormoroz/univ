#include <string>
#include <iostream>
using namespace std;

template<typename T>
int find_min(const T *a, int n) {
	if (n <= 0 || !a)
		return -1;
	int j = 0;
	for (int i = 1; i < n; ++i)
		if (a[i] < a[j])
			j = i;
	return j;
}

template<typename T, size_t n>
int find_min(const T (&a)[n]) {
	if (n <= 0)
		return -1;
	int j = 0;
	for (int i = 1; i < n; ++i)
		if (a[i] < a[j])
			j = i;
	return j;
}

int main() {
	int a[] = {1, 4, 0, -3, 8};
	float *b = new float[5]{1.23, 4.56, 0.8, -3.9, 8.9};
	double c[] = {1.5, 4., 0., -3.8, 8.};
	string d[] = {"foo", "bar", "cat", "dog", "owl"};
	cout << a[find_min(a)] << endl;
	cout << b[find_min(b, 5)] << endl;
	cout << c[find_min(c)] << endl;
	cout << d[find_min(d)] << endl;
	delete[] b;
}

