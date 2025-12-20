#ifndef ICANVAS_H_
#define ICANVAS_H_

#include "PaintProperties.h"
#include "Geometry.h"
#include <string>
#include <sstream>

// Abstract canvas interface
class ICanvas {
public:
    virtual ~ICanvas() = default;

    // Primitive drawing operations
    virtual void drawLine(size_t x1, size_t y1, size_t x2, size_t y2,
        const IPen& pen) = 0;

    virtual void drawRectangle(const Geometry& geom,
        const IPen& pen,
        const IBrush& brush) = 0;

    virtual void drawCircle(size_t centerX, size_t centerY, size_t radius,
        const IPen& pen,
        const IBrush& brush) = 0;

    virtual void drawText(size_t x, size_t y,
        const std::string& text,
        const std::string& font,
        size_t fontSize,
        const std::string& color,
        const std::string& alignment = "start") = 0;


    virtual void clear() = 0;
    virtual std::string getContent() const = 0;
    virtual void setBackground(const std::string& color) = 0;


    virtual size_t getWidth() const = 0;
    virtual size_t getHeight() const = 0;
};

#endif // ICANVAS_H_