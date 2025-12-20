#include "BaseSlideObject.h"

BaseSlideObject::BaseSlideObject(const std::string& name, const Geometry& geom)
    : name(name), geometry(geom) {
}

std::string BaseSlideObject::getName() const {
    return name;
}

void BaseSlideObject::setName(const std::string& n) {
    name = n;
}

Geometry BaseSlideObject::getGeometry() const {
    return geometry;
}

void BaseSlideObject::setGeometry(const Geometry& geom) {
    geometry = geom;
}

void BaseSlideObject::paint(const IPainter& painter, ICanvas& canvas) const {
    painter.draw(this, canvas);
}