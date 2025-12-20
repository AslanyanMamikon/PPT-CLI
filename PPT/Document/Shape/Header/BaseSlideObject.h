#ifndef BASE_SLIDE_OBJECT_H_
#define BASE_SLIDE_OBJECT_H_

#include "SlideObject.h"
#include "IPainter.h"
#include "ICanvas.h"

class BaseSlideObject : public SlideObject {
protected:
    std::string name;
    Geometry geometry;

public:
    BaseSlideObject(const std::string& name, const Geometry& geom);
    virtual ~BaseSlideObject() = default;

    std::string getName() const override;
    void setName(const std::string& n) override;
    Geometry getGeometry() const override;
    void setGeometry(const Geometry& geom) override;

    void paint(const IPainter& painter, ICanvas& canvas) const override;
};

#endif // BASE_SLIDE_OBJECT_H_