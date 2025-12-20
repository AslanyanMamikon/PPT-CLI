#include "Line.h"
#include <iostream>
#include <algorithm>

Line::Line(const std::string& name,
    size_t startX, size_t startY, size_t endX, size_t endY,
    const std::string& color,
    size_t width)
    : BaseSlideObject(name,
        Geometry(std::min(startX, endX), std::min(startY, endY),
            std::max(startX, endX), std::max(startY, endY))),
    x1(startX), y1(startY), x2(endX), y2(endY),
    color(color), width(width) {
}

std::string Line::getType() const {
    return "Line";
}

void Line::draw() const {
    std::cout << "Line '" << name << "' from ("
        << x1 << "," << y1 << ") to ("
        << x2 << "," << y2 << ")"
        << " [color: " << color << ", width: " << width << "]\n";
}

std::unique_ptr<SlideObject> Line::clone() const {
    return std::make_unique<Line>(*this);
}

void Line::setGeometry(const Geometry& geom) {
    geometry = geom;
    Point tl = geom.getTopLeft();
    Point br = geom.getBottomRight();

    // Preserve line direction when geometry changes
    bool x1WasSmaller = (x1 <= x2);
    bool y1WasSmaller = (y1 <= y2);

    if (x1WasSmaller && y1WasSmaller) {
        x1 = tl.x; y1 = tl.y;
        x2 = br.x; y2 = br.y;
    }
    else if (!x1WasSmaller && y1WasSmaller) {
        x1 = br.x; y1 = tl.y;
        x2 = tl.x; y2 = br.y;
    }
    else if (x1WasSmaller && !y1WasSmaller) {
        x1 = tl.x; y1 = br.y;
        x2 = br.x; y2 = tl.y;
    }
    else {
        x1 = br.x; y1 = br.y;
        x2 = tl.x; y2 = tl.y;
    }
}

size_t Line::getStartX() const {
    return x1;
}

size_t Line::getStartY() const {
    return y1;
}

size_t Line::getEndX() const {
    return x2;
}

size_t Line::getEndY() const {
    return y2;
}

void Line::setStartPoint(size_t x, size_t y) {
    x1 = x;
    y1 = y;

    geometry = Geometry(std::min(x1, x2), std::min(y1, y2),
        std::max(x1, x2), std::max(y1, y2));
}

void Line::setEndPoint(size_t x, size_t y) {
    x2 = x;
    y2 = y;
    
    geometry = Geometry(std::min(x1, x2), std::min(y1, y2),
        std::max(x1, x2), std::max(y1, y2));
}

std::string Line::getColor() const {
    return color;
}

void Line::setColor(const std::string& c) {
    color = c;
}

size_t Line::getWidth() const {
    return width;
}

void Line::setWidth(size_t w) {
    width = w;
}