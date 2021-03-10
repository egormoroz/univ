template<typename T, size_t N>
class Array {
    T data[N];
public:
    using Self = Array<T, N>;
    Array() = default;
    Array(const T *data) {
        for (size_t i = 0; i < N; ++i)
            this->data[i] = data[i];
    }
    explicit Array(T x) {
        for (size_t i = 0; i < N; ++i)
            data[i] = x;
    }
    Array(const Self &y) {
        for (size_t i = 0; i < N; ++i)
            data[i] = y.data[i];
    }

    size_t size() const { return N; }

    T& operator[](size_t idx) { return data[idx]; }
    const T& operator[](size_t idx) const { return data[idx]; }

    Self& operator=(const Self &y) {
        for (size_t i = 0; i < N; ++i)
            data[i] = y.data[i];
    }

    ~Array() = default;
};

