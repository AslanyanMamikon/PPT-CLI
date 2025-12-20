#ifndef SLIDE_OBJECT_H_
#define SLIDE_OBJECT_H_

#include "Geometry.h"
#include <iostream>
#include <string>
#include <memory>

class IPainter;
class ICanvas;

class SlideObject {
public:
    virtual ~SlideObject() = default;

    virtual std::string getName() const = 0;
    virtual void setName(const std::string& name) = 0;
    virtual std::string getType() const = 0;

    virtual void draw() const = 0;

    // Canvas rendering
    virtual void paint(const IPainter& painter, ICanvas& canvas) const = 0;

    virtual Geometry getGeometry() const = 0;
    virtual void setGeometry(const Geometry& geom) = 0;

    virtual std::unique_ptr<SlideObject> clone() const = 0;
};

#endif // SLIDE_OBJECT_H_