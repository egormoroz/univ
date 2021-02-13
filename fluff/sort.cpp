#include <iostream>
using namespace std;
const int N = 16;
int a[N];

void bubblesort() {
    for (int i = 0; i < N; ++i) {
        for (int j = 1; j < N; ++j) {
            if (a[j - 1] > a[j])
                swap(a[j - 1], a[j]);
        }
    }
}

void inssort() {
    for (int i = 1; i < N - 1; ++i) {
        int x = a[i + 1], j;
        for (j = i; j >= 0 && x < a[j]; --j) {
            a[j + 1] = a[j];
        }
        a[j+1] = x;
    }
}

void selsort() {
    for (int i = N - 1; i >= 0; --i) {
        int k = 0;
        for (int j = 1; j <= i; ++j) {
            if (a[j] > a[k])
                k = j;
        }
        swap(a[i], a[k]);
    }
}

int main() {
    for (int i = 0; i < N; ++i)
        a[i] = rand() % N;
    selsort();
    for (int i : a)
        cout << i << ' ';
}
