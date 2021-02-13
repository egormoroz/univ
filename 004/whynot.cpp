#include <iostream>
//#include <limits>
using namespace std;

int main() {
    //i hope it's x86; if it's not known - use numeric_limits<int>::max()
    const int I32_MAX = 0xFFFFFFFF >> 1;
    int m, n;
    //m rows, n cols
    cin >> m >> n;
    int c = I32_MAX, k = 0;
    int *a = new int[m * n];
    for (int i = 0; i < m; ++i) {
        int b = I32_MAX;
        for (int j = 0; j < n; ++j) {
            cin >> a[i * n + j];
            if (a[i * n + j] < b)
                b = a[i * n + j];
        }
        if (b < c) {
            k = i;
            c = b;
        }
    }

    for (int i = 0; i < n; ++i)
        cout << a[k * n + i] << ' ';
    cout << '\n';

    //if going for perfomance, create 2 for loops to reduce branching
    for (int i = 0; i < m; ++i) {
        if (i != k) {
            for (int j = 0; j < n; ++j)
                cout << a[i * n + j] << ' ';
            cout << '\n';
        }
    }

    delete[] a;
}

