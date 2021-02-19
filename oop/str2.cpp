#include <cstring>
#include <utility>
#include <iostream>
#include <cstdint>
using namespace std;

//rounds to next power of 2
constexpr uint32_t align(uint32_t n) noexcept {
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
}

struct Dynamic {
    char* data;
    size_t len;
    size_t cap;
};

const size_t N = align(sizeof(Dynamic) + 1) - 1;

class String {
    union U {
        Dynamic a;
        char b[N + 1];
    } u;

    void alloc(size_t n) {
        u.a.cap = align(n);
        u.a.data = new char[u.a.cap];
    }

    U release() noexcept {
        U t = u;
        u.b[N] = 0;
        return t;
    }

public:
    String() noexcept {
        memset(&u, 0, sizeof(u));
        u.b[N] = N;
    }

    String(const String& other) {
        char n = other.u.b[N];
        if (n >= 0) {
            u = other.u;
        } else {
            u.a.len = other.u.a.len;
            alloc(u.a.len + 1);
            memcpy(u.a.data, other.u.a.data, u.a.len + 1);
        }
    }

    String(const char* s) {
        size_t n = strlen(s);
        if (n <= N) {
            memcpy(u.b, s, n + 1);
            u.b[N] = N - n;
        } else {
            u.b[N] = -1;
            alloc(n + 1);
            u.a.len = n;
            memcpy(u.a.data, s, n + 1);
        }
    }

    String(String &&other) noexcept
        : u(other.release())
    {}

    void append(const String& other) {
        append(other.c_str(), other.length());
    }

    void append(const char* s) {
        append(s, strlen(s));
    }

    void append(const char* s, size_t n) {
        size_t old_len = length(), new_len = n + old_len;
        if (new_len < N) {
            memcpy(u.b + old_len, s, n + 1);
            u.b[N] = N - new_len;
        } else {
            if (u.b[N] < 0 && u.a.cap >= new_len + 1) {
                u.a.len = new_len;
                memcpy(u.a.data + old_len, s, n + 1);
            } else {
                size_t cap = align(new_len + 1);
                char* buf = new char[cap];

                if (u.b[N] < 0) {
                    memcpy(buf, u.a.data, old_len);
                    delete[] u.a.data;
                } else {
                    memcpy(buf, u.b, old_len);
                    u.b[N] = -1;
                }

                memcpy(buf + old_len, s, n + 1);
                u.a.data = buf;
                u.a.len = new_len;
                u.a.cap = cap;
            }
        }
    }

    size_t length() const noexcept {
        return u.b[N] < 0 ? u.a.len : N - u.b[N];
    }

    const char* c_str() const {
        return u.b[N] < 0 ? u.a.data : u.b;
    }

    ~String() {
        if (u.b[N] < 0) {
            delete[] u.a.data;
        }
    }
};

int main() {
    String s("hello");
    s.append(" world");
    s.append(" lalalal");
}

