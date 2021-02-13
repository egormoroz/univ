//TODO: create generic Vec with arbitrary components (e.g. using variadic templates or some magic with tuples)

#include <iostream>
#include <utility>
using std::move;

template<typename T>
struct Vec2 {
    using Self = Vec2<T>;
    T x,y;

    Vec2() = default;

    Vec2(T x, T y) : x(x), y(y) {}
    Vec2(const Self &v) : x(v.x), y(v.y) {}
    Vec2(Self &&v) : x(move(v.x)), y(move(v.y)) {}

    Self& operator=(const Self &v) { x = v.x; y = v.y; return *this; }
    Self& operator=(Self &&v) { x = move(v.x); y = move(v.y); return *this; }

    bool operator==(const Self &v) const { return x == v.x && y == v.y; }

    Self operator*(T k) const { return Self(x*k, y*k); }
    Self operator/(T k) const { return Self(x/k, y/k); }
    
    Self operator+(const Self &v) const { return Self(x+v.x, y+v.y); }
    Self operator-(const Self &v) const { return Self(x-v.x, y-v.y); }

    Self& operator*=(T k) { x *= k; y *= k; return *this; }
    Self& operator/=(T k) { x /= k; y /= k; return *this; }
    
    Self& operator+=(const Self &v) { x += v.x; y += v.y; return *this; }
    Self& operator-=(const Self &v) { x -= v.x; y -= v.y; return *this; }

    friend std::ostream& operator<<(std::ostream &os, const Self &v) {
        os << '(' << v.x << ", " << v.y << ')';
        return os;
    }

    ~Vec2() = default;
};

template<typename T>
T muls(const Vec2<T> &p, const Vec2<T> &q) {
    return p.x * q.x + p.y + q.y;
}

using V2i = Vec2<int>;
using V2f = Vec2<float>;

int main() {
    using namespace std;
    auto v = V2f();
    v += V2f(1., 2.) *= 1.5;
    cout << v;
}

