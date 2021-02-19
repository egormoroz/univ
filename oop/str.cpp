#include <cstring>
#include <utility>
#include <iostream>
using namespace std;

class String {
    char* data = nullptr;
    int len = 0;
public:
    String() = default;
    String(const char* s) {
        len = strlen(s);
        data = new char[len + 1];
        memcpy(data, s, len + 1);
    }

    explicit String(int n, char ch)
        : len(n), data(new char[n + 1]) {
        memset(data, ch, len);
        data[len] = 0;
    }

    String(String&& other)
        : data(exchange(other.data, nullptr)), len(exchange(other.len, 0)) {
    }
    String(const String& other)
        : data(new char[len + 1]), len(other.len) {
        memcpy(data, other.data, len + 1);
    }

    void clear() {
        if (data) {
            delete[] data;
            len = 0;
        }
    }

    int length() const { return len; }

    String& operator=(const String& other) {
        clear();
        len = other.len;
        data = new char[len + 1];
        memcpy(data, other.data, len + 1);
        return *this;
    }
    String& operator=(String&& other) {
        clear();
        data = exchange(other.data, nullptr);
        len = exchange(other.len, 0);
        return *this;
    }

    String& operator=(const char* s) {
        *this = String(s);
        return *this;
    }

    ~String() {
        if (data)
            delete[] data;
    }

    friend ostream& operator<<(ostream& out, const String& s);
};

ostream& operator<<(ostream& out, const String& s) {
    if (s.data)
        out << s.data;
    return out;
}

int main() {
    String a = "hello world", b(5, 'Z');
    cout << a << '\n' << b;
}

