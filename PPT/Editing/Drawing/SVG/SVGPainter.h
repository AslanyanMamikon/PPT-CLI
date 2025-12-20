#ifndef SVG_PAINTER_H_
#define SVG_PAINTER_H_

#include "IPainter.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include "TextObject.h"
#include "IPen.h"
#include "IBrush.h"

class SVGPainter : public IPainter {
public:
    SVGPainter() = default;

    void draw(const SlideObject* obj, ICanvas& canvas) const override;

    void drawRectangle(const Rectangle* rect, ICanvas& canvas) const override;
    void drawCircle(const Circle* circle, ICanvas& canvas) const override;
    void drawLine(const Line* line, ICanvas& canvas) const override;
    void drawText(const TextObject* text, ICanvas& canvas) const override;
};

#endif // SVG_PAINTER_H_