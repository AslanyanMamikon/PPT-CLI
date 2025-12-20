#ifndef IPAINTER_H_
#define IPAINTER_H_

#include "ICanvas.h"

class SlideObject;
class Rectangle;
class Circle;
class Line;
class TextObject;

class IPainter {
public:
    virtual ~IPainter() = default;

    // Draw a slide object
    virtual void draw(const SlideObject* obj, ICanvas& canvas) const = 0;

    // Type-specific drawing methods
    virtual void drawRectangle(const Rectangle* rect, ICanvas& canvas) const = 0;
    virtual void drawCircle(const Circle* circle, ICanvas& canvas) const = 0;
    virtual void drawLine(const Line* line, ICanvas& canvas) const = 0;
    virtual void drawText(const TextObject* text, ICanvas& canvas) const = 0;
};

#endif // IPAINTER_H_