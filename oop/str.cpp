#include <cstring>
#include <utility>
#include <iostream>
using namespace std;

class String {
    char* data = nullptr;
    int len = 0;
public:
    String() = default;
    String(const char* s, int n=-1) {
        if (n != -1)
            len = n;
        else
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
        : String(other.data, other.len)
    {}

    void append(const char *s, int n=-1) {
        if (n == -1)
            n = strlen(s);
        char *buf = new char[len+n+1];
        memcpy(buf, data, len);
        memcpy(buf + len, s, n+1);
        if (data)
            delete[] data;
        data = buf;
        len += n;
    }

    void append(const String &other) {
        append(other.data, other.len);
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
    a.append(b);
    a.append("\nyeaaaah");
    cout << a;
}

