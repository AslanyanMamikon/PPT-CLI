#ifndef LINE_H_
#define LINE_H_

#include "BaseSlideObject.h"

class Line : public BaseSlideObject {
private:
    size_t x1, y1, x2, y2;
    std::string color;
    size_t width;

public:
    Line(const std::string& name,
        size_t startX, size_t startY, size_t endX, size_t endY,
        const std::string& color = "black",
        size_t width = 1);

    std::string getType() const override;
    void draw() const override;
    std::unique_ptr<SlideObject> clone() const override;

    // Override to update line endpoints
    void setGeometry(const Geometry& geom) override;

    // Line-specific methods
    size_t getStartX() const;
    size_t getStartY() const;
    size_t getEndX() const;
    size_t getEndY() const;
    void setStartPoint(size_t x, size_t y);
    void setEndPoint(size_t x, size_t y);
    std::string getColor() const;
    void setColor(const std::string& c);
    size_t getWidth() const;
    void setWidth(size_t w);
};

#endif // LINE_H_