#include "SlideObject.h"

SlideObject& SlideObject::operator=(const SlideObject& other)
{
    if (this != &other)
    {
        type = other.type;
        name = other.name;
        color = other.color;
        fontSize = other.fontSize;
        pos = other.pos;
        size = other.size;

        if (other.shape) {
            shape = other.shape->clone();
        }
        else {
            shape.reset();
        }
    }
    return *this;
}

void SlideObject::draw() const
{
    if (shape)
        shape->draw();
    else
    {
        std::cout << "SlideObject '" << name << "' (type: "
            << static_cast<int>(type) << ") at ("
            << pos.x << "," << pos.y << ") "
            << size.width << "x" << size.height << "\n";
    }
}

BoundingBox SlideObject::getBounds() const
{
    if (shape)
        return shape->getBounds();

    return BoundingBox(pos.x, pos.y, pos.x + size.width, pos.y + size.height);
}

void SlideObject::move(size_t deltaX, size_t deltaY)
{
    if (shape)
        shape->move(deltaX, deltaY);

    pos.x += deltaX;
    pos.y += deltaY;
}

void SlideObject::resize(size_t newWidth, size_t newHeight)
{
    if (shape)
        shape->resize(newWidth, newHeight);

    size.width = newWidth;
    size.height = newHeight;
}

bool SlideObject::containsPoint(size_t x, size_t y) const
{
    return getBounds().contains(x, y);
}

bool SlideObject::intersects(const SlideObject& other) const
{
    return getBounds().intersects(other.getBounds());
}

bool SlideObject::isText() const { return type == ObjectType::TEXT; }
bool SlideObject::isImage() const { return type == ObjectType::IMAGE; }
bool SlideObject::isShape() const { return type == ObjectType::SHAPE; }