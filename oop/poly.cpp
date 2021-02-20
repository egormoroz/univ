using uint8_t = unsigned char;

struct Surface;

struct Drawable {
    friend struct Surface;

    Drawable() = default;
    virtual ~Drawable() = default;
protected:
    virtual void draw(Surface &) const = 0;
};

struct Surface {
    void clear() {}
    void draw(const Drawable &d) {
        d.draw(*this);
    }
    void render() {}
};

template<typename T>
struct Rect {
    //basically, vertices
    T left, top, right, bottom;
};

template<typename T>
struct Vec2 {
    T x,y;
};

struct Color {
    uint8_t r,g,b;
};

using RectI = Rect<int>;
using RectF = Rect<float>;
using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;

struct Shape : public Drawable {
    Color fill_clr, outline_clr;
    float outline_thickness;
};

struct Circle : public Shape {
    float radius;
    Vec2f center;
protected:
    virtual void draw(Surface &surf) const {
        //...
    }
};

struct Rectangle : public Shape {
    RectF bounds;
    Color color;
protected:
    virtual void draw(Surface &surf) const {
        //...
    }
};

struct Sprite : public Drawable {
    int texture_id;
    RectI bounds;

protected:
    virtual void draw(Surface &surf) const override {
        //...
    }
};

int main() {
    Surface surf;
    Sprite s;
    Circle c;
    Rectangle r;

    Drawable* d[3] = { &s, &c, &r };

    while (true) {
        surf.clear();
        for (auto i : d)
            surf.draw(*i);
        surf.render();
    }
}

