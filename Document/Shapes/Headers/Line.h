#ifndef LINE_H_
#define LINE_H_

#include "BaseShape.h"
#include <iostream>
#include <cmath>

class Line : public BaseShape
{
public:
    Line(const std::string& name, 
        size_t startX, size_t startY, size_t endX, size_t endY,
        const std::string& color = "black", 
        size_t width = 1)
        : BaseShape(name,
                    BoundingBox({ std::min(startX, endX), std::min(startY, endY) },
                        { std::max(startX, endX), std::max(startY, endY) }),
                    "none", color, width),
        x1(startX), y1(startY), x2(endX), y2(endY) {}

    void draw() const override;
    void move(size_t deltaX, size_t deltaY) override;
    std::string getType() const override;

    std::unique_ptr<IShape> clone() const override;

    // Line-specific methods
    void setStartPoint(size_t x, size_t y);
    void setEndPoint(size_t x, size_t y);

    size_t getStartX() const;
    size_t getStartY() const;
    size_t getEndX() const;
    size_t getEndY() const;

private:
    void updateBounds();

private:
	size_t x1, y1;
	size_t x2, y2;
};

#endif // !LINE_H_
