#ifndef PAINT_PROPERTIES_H_
#define PAINT_PROPERTIES_H_

#include "IPen.h"
#include "IBrush.h"
#include <memory>


class PaintProperties {
private:
    std::unique_ptr<IPen> pen;
    std::unique_ptr<IBrush> brush;

public:
    PaintProperties()
        : pen(std::make_unique<Pen>()),
        brush(std::make_unique<Brush>()) {
    }

    PaintProperties(std::unique_ptr<IPen> p, std::unique_ptr<IBrush> b)
        : pen(std::move(p)), brush(std::move(b)) {
    }

    // Copy constructor
    PaintProperties(const PaintProperties& other)
        : pen(other.pen ? other.pen->clone() : nullptr),
        brush(other.brush ? other.brush->clone() : nullptr) {
    }

    // Copy assignment
    PaintProperties& operator=(const PaintProperties& other) {
        if (this != &other) {
            pen = other.pen ? other.pen->clone() : nullptr;
            brush = other.brush ? other.brush->clone() : nullptr;
        }
        return *this;
    }

    // Move constructor and assignment
    PaintProperties(PaintProperties&&) = default;
    PaintProperties& operator=(PaintProperties&&) = default;

    IPen* getPen() const { return pen.get(); }
    IBrush* getBrush() const { return brush.get(); }

    void setPen(std::unique_ptr<IPen> p) { pen = std::move(p); }
    void setBrush(std::unique_ptr<IBrush> b) { brush = std::move(b); }

    // Convenience methods
    void setPenColor(const std::string& color) {
        if (pen) pen->setColor(color);
    }

    void setPenWidth(size_t width) {
        if (pen) pen->setWidth(width);
    }

    void setBrushColor(const std::string& color) {
        if (brush) brush->setColor(color);
    }

    void setBrushOpacity(double opacity) {
        if (brush) brush->setOpacity(opacity);
    }
};

#endif // PAINT_PROPERTIES_H_