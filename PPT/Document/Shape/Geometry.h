#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <cstddef>
#include <algorithm>

struct Point {
    size_t x;
    size_t y;

    Point(size_t x = 0, size_t y = 0) : x(x), y(y) {}
};


class Geometry {
public:
    Geometry() : topLeft(0, 0), bottomRight(0, 0) {}

    Geometry(Point p1, Point p2) : topLeft(p1), bottomRight(p2) {}

    Geometry(size_t x1, size_t y1, size_t x2, size_t y2)
        : topLeft(x1, y1), bottomRight(x2, y2) {}

    // Simple getters - no logic
    size_t getWidth() const { return bottomRight.x - topLeft.x; }
    size_t getHeight() const { return bottomRight.y - topLeft.y; }
    Point getTopLeft() const { return topLeft; }
    Point getBottomRight() const { return bottomRight; }
    size_t getCenterX() const { return (topLeft.x + bottomRight.x) / 2; }
    size_t getCenterY() const { return (topLeft.y + bottomRight.y) / 2; }

    void setTopLeft(size_t x, size_t y) {
        topLeft.x = x;
        topLeft.y = y;
    }

    void setBottomRight(size_t x, size_t y) {
        bottomRight.x = x;
        bottomRight.y = y;
    }

private:
    Point topLeft;
    Point bottomRight;
};


namespace GeometryUtils {

    // Move a geometry by delta
    inline Geometry move(const Geometry& geom, size_t deltaX, size_t deltaY) {
        Point tl = geom.getTopLeft();
        Point br = geom.getBottomRight();
        return Geometry(tl.x + deltaX, tl.y + deltaY,
            br.x + deltaX, br.y + deltaY);
    }

    // Resize a geometry
    inline Geometry resize(const Geometry& geom, size_t newWidth, size_t newHeight) {
        Point tl = geom.getTopLeft();
        return Geometry(tl.x, tl.y, tl.x + newWidth, tl.y + newHeight);
    }

    // Check if a point is inside a geometry
    inline bool contains(const Geometry& geom, size_t x, size_t y) {
        Point tl = geom.getTopLeft();
        Point br = geom.getBottomRight();
        return x >= tl.x && x <= br.x && y >= tl.y && y <= br.y;
    }

    // Check if two geometries intersect
    inline bool intersects(const Geometry& g1, const Geometry& g2) {
        Point tl1 = g1.getTopLeft();
        Point br1 = g1.getBottomRight();
        Point tl2 = g2.getTopLeft();
        Point br2 = g2.getBottomRight();

        return !(br1.x < tl2.x || br2.x < tl1.x ||
            br1.y < tl2.y || br2.y < tl1.y);
    }
}

#endif // GEOMETRY_H_