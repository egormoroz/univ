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
    int **a = new int*[m];
    for (int i = 0; i < m; ++i) {
        a[i] = new int[n];
        int b = I32_MAX;
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
            if (a[i][j] < b)
                b = a[i][j];
        }
        if (b < c) {
            k = i;
            c = b;
        }
    }

    int *r = a[k];
    a[k] = a[0];
    a[0] = r;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j)
            cout << a[i][j] << ' ';
        cout << '\n';
    }

    for (int i = 0; i < m; ++i)
        delete[] a[i];
    delete[] a;
}

