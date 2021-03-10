#include <initializer_list>
#include <algorithm>
#include <cstring>
#include <iostream>

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


//Interreferencing via references/pointers is considered UB here
//Excessive T c-tor calls, can be reduced by allocating not with operator new
//However, new guarantees, that everything is initialized
template<typename T, typename CRet = const T&>
class Array {
    using Self = Array<T>;
    size_t len = 0, cap = 0;
    T* data = 0;

    void alloc(size_t n) {
        data = new T[n];
        cap = n;
        len = n;
    }

    void grow(size_t n) {
        if (n <= len)
            return;
        if (n <= cap) {
            len = n;
            return;
        }
        cap = align(n);
        T* buf = new T[cap];
        if (data) {
            memcpy(buf, data, len * sizeof(T)); //gotta be careful, possible UB
            delete[] data;
        }
        len = n;
        data = buf;
    }
public:
    //c-tors
    Array() = default;

    Array(size_t n, T x) {
        alloc(n);
        //std::fill is better
        for (size_t i = 0; i < n; ++i)
            data[i] = x;
    }

    Array(std::initializer_list<T> l) {
        alloc(l.size());
        T* data = this->data;
        for (auto& i : l)
            *(data++) = i;
    }

    Array(const Self& y) {
        alloc(y.len);
        //might be turned into memcpy, hence not just for loop
        std::copy(y.data, y.data + y.len, data);
    }

    //manip/access

    void extend(const Self& y) {
        size_t old = len;
        grow(len + y.len);
        std::copy(y.data, y.data + y.len, data + old);
    }

    void push(T&& x) {
        grow(len + 1);
        data[len - 1] = x;
    }

    T pop() {
        //TODO: throw if len == 0
        T x = std::move(data[len - 1]);
        --len;
    }

    void clear() { len = 0; }

    size_t size() const { return len; }
    size_t capacity() const { return cap; }

    //TODO: throw if out of range
    CRet operator[](size_t idx) const { return data[idx]; }
    //TODO: throw if out of range
    T& operator[](size_t idx) { return data[idx]; }

    Self& operator=(const Self& y) {
        if (cap < y.len) {
            if (data)
                delete[] data;
            alloc(y.len);
        }
        len = y.len;
        //calling T::operator= is safe, because alloc uses new, which calls constructor
        std::copy(y.data, y.data + y.len, data);
        return *this;
    }

    //d-tor
    ~Array() {
        if (data)
            delete[] data;
    }
};

int main() {
    using std::cout;
    using A = Array<int>;
    A t(3, 0);
    A a(t);
    A b = { 1, 2, 3 };
    a.extend(b);
    a.push(4);
    a.push(5);
    cout << "capacity: " << a.capacity() << '\n';
    for (size_t i = 0; i < a.size(); ++i)
        cout << a[i] << ' ';
}

