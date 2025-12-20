#include "Circle.h"
#include <iostream>

Circle::Circle(const std::string& name,
    size_t centerX, size_t centerY, size_t rad,
    const std::string& fillColor,
    const std::string& borderColor,
    size_t borderWidth)
    : BaseSlideObject(name,
        Geometry(centerX - rad, centerY - rad,
            centerX + rad, centerY + rad)),
    fillColor(fillColor),
    borderColor(borderColor),
    borderWidth(borderWidth),
    radius(rad) {}

std::string Circle::getType() const {
    return "Circle";
}

void Circle::draw() const {
    size_t centerX = geometry.getCenterX();
    size_t centerY = geometry.getCenterY();
    size_t rad = geometry.getWidth() / 2;

    std::cout << "Circle '" << name << "' at center ("
        << centerX << "," << centerY << ") "
        << "radius: " << rad
        << " [fill: " << fillColor << ", border: " << borderColor << "]\n";
}

std::unique_ptr<SlideObject> Circle::clone() const {
    return std::make_unique<Circle>(*this);
}

void Circle::setGeometry(const Geometry& geom) {
    geometry = geom;
    radius = geometry.getWidth() / 2;
}

size_t Circle::getRadius() const {
    return radius;
}

void Circle::setRadius(size_t r) {
    radius = r;
    size_t centerX = geometry.getCenterX();
    size_t centerY = geometry.getCenterY();
    geometry = Geometry(centerX - radius, centerY - radius,
        centerX + radius, centerY + radius);
}

std::string Circle::getFillColor() const {
    return fillColor;
}

void Circle::setFillColor(const std::string& color) {
    fillColor = color;
}

std::string Circle::getBorderColor() const {
    return borderColor;
}

void Circle::setBorderColor(const std::string& color) {
    borderColor = color;
}

size_t Circle::getBorderWidth() const {
    return borderWidth;
}

void Circle::setBorderWidth(size_t width) {
    borderWidth = width;
}