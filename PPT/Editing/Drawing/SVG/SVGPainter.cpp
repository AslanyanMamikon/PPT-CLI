#include "SVGPainter.h"

void SVGPainter::draw(const SlideObject* obj, ICanvas& canvas) const {
    if (!obj) return;

    std::string type = obj->getType();

    if (type == "Rectangle") {
        drawRectangle(dynamic_cast<const Rectangle*>(obj), canvas);
    }
    else if (type == "Circle") {
        drawCircle(dynamic_cast<const Circle*>(obj), canvas);
    }
    else if (type == "Line") {
        drawLine(dynamic_cast<const Line*>(obj), canvas);
    }
    else if (type == "Text") {
        drawText(dynamic_cast<const TextObject*>(obj), canvas);
    }
}

void SVGPainter::drawRectangle(const Rectangle* rect, ICanvas& canvas) const {
    if (!rect) return;

    // Create pen and brush from rectangle properties
    Pen pen(rect->getBorderColor(), rect->getBorderWidth());
    Brush brush(rect->getFillColor());

    canvas.drawRectangle(rect->getGeometry(), pen, brush);
}

void SVGPainter::drawCircle(const Circle* circle, ICanvas& canvas) const {
    if (!circle) return;

    Geometry geom = circle->getGeometry();
    size_t centerX = geom.getCenterX();
    size_t centerY = geom.getCenterY();
    size_t radius = circle->getRadius();

    Pen pen(circle->getBorderColor(), circle->getBorderWidth());
    Brush brush(circle->getFillColor());

    canvas.drawCircle(centerX, centerY, radius, pen, brush);
}

void SVGPainter::drawLine(const Line* line, ICanvas& canvas) const {
    if (!line) return;

    Pen pen(line->getColor(), line->getWidth());

    canvas.drawLine(line->getStartX(), line->getStartY(),
        line->getEndX(), line->getEndY(), pen);
}

void SVGPainter::drawText(const TextObject* text, ICanvas& canvas) const {
    if (!text) return;

    Geometry geom = text->getGeometry();
    Point topLeft = geom.getTopLeft();

    // Calculate text position based on alignment
    size_t x = topLeft.x;
    std::string alignment = "start";

    if (text->getAlignment() == "center") {
        x = geom.getCenterX();
        alignment = "middle";
    }
    else if (text->getAlignment() == "right") {
        x = topLeft.x + geom.getWidth();
        alignment = "end";
    }

    // Vertically center text in its box
    size_t y = topLeft.y + (geom.getHeight() / 2) + (text->getFontSize() / 3);

    canvas.drawText(x, y, text->getContent(),
        text->getFont(), text->getFontSize(),
        text->getColor(), alignment);
}