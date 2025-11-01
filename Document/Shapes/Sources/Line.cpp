#include "Line.h"

void Line::draw() const
{
    std::cout << "Line '" << name << "' from ("
        << x1 << "," << y1 << ") to ("
        << x2 << "," << y2 << ")"
        << " [color: " << borderColor << ", width: " << borderWidth << "]\n";
}

void Line::move(size_t deltaX, size_t deltaY)
{
    x1 += deltaX; y1 += deltaY;
    x2 += deltaX; y2 += deltaY;
    BaseShape::move(deltaX, deltaY);
}

std::string Line::getType() const { return "Line"; }

std::unique_ptr<IShape> Line::clone() const
{
    return std::make_unique<Line>(*this);
}

// Line-specific methods
void Line::setStartPoint(size_t x, size_t y)
{
    x1 = x;
    y1 = y;
    updateBounds();
}

void Line::setEndPoint(size_t x, size_t y)
{
    x2 = x;
    y2 = y;
    updateBounds();
}

size_t Line::getStartX() const { return x1; }
size_t Line::getStartY() const { return y1; }
size_t Line::getEndX() const { return x2; }
size_t Line::getEndY() const { return y2; }

void Line::updateBounds()
{
    bounds.setTopLeft(std::min(x1, x2), std::min(y1, y2));
    bounds.setBottomRight(std::max(x1, x2), std::max(y1, y2));
}