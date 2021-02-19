using uint8_t = unsigned char;

struct Drawable;

struct Surface {
    void clear() {}
    void draw(const Drawable &d) {
        d.draw(*this);
    }
    void render() {}
}

struct Drawable {
    friend struct Surface;

    Drawable() = default;
    virtual ~Drawable() = default;
protected:
    virtual void draw(Surface &) const = 0;
}

template<typename T>
struct Rect {
    //basically, vertices
    T left, top, right, bottom;
}

struct Color {
    uint8_t r,g,b;
}

using RectI = Rect<int>;
using RectF = Rect<float>;

struct Rectangle : public Drawable {
    RectF bounds;
    Color color;
protected:
    virtual void draw(Surface &surf) const
}

struct Sprite : public Drawable {
    int texture_id;
    RectI bounds;

protected:
    virtual void draw(Surface &surf) const override {
        //...
    }
}

