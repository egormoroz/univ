#include <iostream>
using namespace std;

int main () {
    int n, k=0, t;
    cin >> n;
    int *a = new int[n];

    for (int i = 0; i < n; ++i)
        cin >> a[i];

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[i] > a[j]) {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
                ++k;
            }
        }
    }
    cout << k;

    delete[] a;
}
