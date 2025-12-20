#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(const std::string& name,
    size_t x, size_t y, size_t width, size_t height,
    const std::string& fillColor,
    const std::string& borderColor,
    size_t borderWidth)
    : BaseSlideObject(name, Geometry(x, y, x + width, y + height)),
    fillColor(fillColor),
    borderColor(borderColor),
    borderWidth(borderWidth) {
}

Rectangle::Rectangle(const std::string& name,
    const Geometry& geom,
    const std::string& fillColor,
    const std::string& borderColor,
    size_t borderWidth)
    : BaseSlideObject(name, geom),
    fillColor(fillColor),
    borderColor(borderColor),
    borderWidth(borderWidth) {
}

std::string Rectangle::getType() const {
    return "Rectangle";
}

void Rectangle::draw() const {
    std::cout << "Rectangle '" << name << "' at ("
        << geometry.getTopLeft().x << ", " << geometry.getTopLeft().y << ") "
        << geometry.getWidth() << "x" << geometry.getHeight()
        << " [fill: " << fillColor << ", border: " << borderColor << "]\n";
}

std::unique_ptr<SlideObject> Rectangle::clone() const {
    return std::make_unique<Rectangle>(*this);
}

std::string Rectangle::getFillColor() const {
    return fillColor;
}

void Rectangle::setFillColor(const std::string& color) {
    fillColor = color;
}

std::string Rectangle::getBorderColor() const {
    return borderColor;
}

void Rectangle::setBorderColor(const std::string& color) {
    borderColor = color;
}

size_t Rectangle::getBorderWidth() const {
    return borderWidth;
}

void Rectangle::setBorderWidth(size_t width) {
    borderWidth = width;
}