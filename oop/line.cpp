#include <cstdio>

struct Point {
    int x,y;
};

bool check(Point a, Point b, Point c) {
    return (a.x - b.x) * (b.y - c.y) - (a.y - b.y) * (b.x - c.x) == 0;
}

int main() {
    Point a,b,c;
    while (true) {
        scanf("%d %d %d %d %d %d", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y);
        printf("%s\n", check(a, b, c) ? "Yes" : "No");
    }
}
