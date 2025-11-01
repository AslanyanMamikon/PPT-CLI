#ifndef SLIDE_OBJECT_H_
#define SLIDE_OBJECT_H_

#include "IShape.h"
#include <iostream>
#include <string>
#include <memory>

enum class ObjectType {
    TEXT, // Text-y shape a te che ??????
    IMAGE,
    SHAPE
};

struct Position {
    size_t x = 0;
    size_t y = 0;
};

struct Size {
    size_t width = 0;
    size_t height = 0;
};

class SlideObject {
public:
    SlideObject(ObjectType type, std::string name)
        : type(type), name(std::move(name)), shape(nullptr) {
    }

    SlideObject(ObjectType type, std::string name, std::unique_ptr<IShape> shapePtr)
        : type(type), name(std::move(name)), shape(std::move(shapePtr)) {
    }

    SlideObject(const SlideObject& other)
        : type(other.type), name(other.name), color(other.color),
        fontSize(other.fontSize), pos(other.pos), size(other.size)
    {
        if (other.shape)
            shape = other.shape->clone();
    }

    SlideObject& operator=(const SlideObject& other);
    void draw() const;
    BoundingBox getBounds() const;
    void move(size_t deltaX, size_t deltaY);
    void resize(size_t newWidth, size_t newHeight);
    bool containsPoint(size_t x, size_t y) const;
    bool intersects(const SlideObject& other) const;
    bool isText() const;
    bool isImage() const;
    bool isShape() const;

public:
    ObjectType type;
    std::string name;     // e.g. "TitleText", "Logo", etc.
    std::string color;    // hex or name ("red", "#ff0000")
    int fontSize = 12;
    Position pos;
    Size size;

    std::unique_ptr<IShape> shape;
};

#endif // SLIDE_OBJECT_H_
