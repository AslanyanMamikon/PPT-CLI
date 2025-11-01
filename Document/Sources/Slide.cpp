#include "Slide.h"

int Slide::getId() const { return id; }
void Slide::setId(int newId) { id = newId; }
const std::string& Slide::getText() const { return text; }

void Slide::addObject(SlideObject&& obj)
{
    if (hasObject(obj.name))
        throw std::runtime_error("Object '" + obj.name + "' already exists");
    objects.push_back(std::move(obj));
}

void Slide::addRectangle(const std::string& name,
    size_t x, size_t y, size_t width, size_t height,
    const std::string& fillColor,
    const std::string& borderColor,
    size_t borderWidth)
{
    auto shape = std::make_unique<Rectangle>(name, x, y, width, height,
        fillColor, borderColor, borderWidth);
    SlideObject obj(ObjectType::SHAPE, name, std::move(shape));
    addObject(std::move(obj));
}

void Slide::addCircle(const std::string& name,
    size_t centerX, size_t centerY, size_t radius,
    const std::string& fillColor,
    const std::string& borderColor,
    size_t borderWidth)
{
    auto shape = std::make_unique<Circle>(name, centerX, centerY, radius,
        fillColor, borderColor, borderWidth);
    SlideObject obj(ObjectType::SHAPE, name, std::move(shape));
    addObject(std::move(obj));
}

void Slide::addText(const std::string& name,
    size_t x, size_t y, size_t width, size_t height,
    const std::string& content,
    const std::string& font,
    size_t fontSize,
    const std::string& color)
{
    auto shape = std::make_unique<TextShape>(name, x, y, width, height,
        content, font, fontSize, color);
    SlideObject obj(ObjectType::TEXT, name, std::move(shape));
    addObject(std::move(obj));
}

void Slide::addLine(const std::string& name,
    size_t x1, size_t y1, size_t x2, size_t y2,
    const std::string& color,
    size_t width)
{
    auto shape = std::make_unique<Line>(name, x1, y1, x2, y2, color, width);
    SlideObject obj(ObjectType::SHAPE, name, std::move(shape));
    addObject(std::move(obj));
}

SlideObject* Slide::getObject(const std::string& name)
{
    auto it = std::find_if(objects.begin(), objects.end(),
        [&name](const SlideObject& obj) { return obj.name == name; });

    return it != objects.end() ? &(*it) : nullptr;
}

const SlideObject* Slide::getObject(const std::string& name) const
{
    auto it = std::find_if(objects.begin(), objects.end(),
        [&name](const SlideObject& obj) { return obj.name == name; });

    return it != objects.end() ? &(*it) : nullptr;
}

SlideObject* Slide::getObjectAt(size_t x, size_t y)
{
    for (auto it = objects.rbegin(); it != objects.rend(); ++it) {
        if (it->containsPoint(x, y)) {
            return &(*it);
        }
    }
    return nullptr;
}

bool Slide::hasObject(const std::string& name) const
{
    return std::any_of(objects.begin(), objects.end(),
        [&name](const SlideObject& obj) { return obj.name == name; });
}

const std::vector<SlideObject>& Slide::getObjects() const
{
    return objects;
}

bool Slide::moveObject(const std::string& name, size_t deltaX, size_t deltaY)
{
    SlideObject* obj = getObject(name);
    if (obj) {
        obj->move(deltaX, deltaY);
        return true;
    }
    return false;
}

bool Slide::resizeObject(const std::string& name, size_t newWidth, size_t newHeight)
{
    SlideObject* obj = getObject(name);
    if (obj) {
        obj->resize(newWidth, newHeight);
        return true;
    }
    return false;
}

bool Slide::bringToFront(const std::string& name)
{
    auto it = std::find_if(objects.begin(), objects.end(),
        [&name](const SlideObject& obj) { return obj.name == name; });

    if (it != objects.end() && it != objects.end() - 1) {
        SlideObject obj = std::move(*it);
        objects.erase(it);
        objects.push_back(std::move(obj));
        return true;
    }
    return false;
}

bool Slide::sendToBack(const std::string& name)
{
    auto it = std::find_if(objects.begin(), objects.end(),
        [&name](const SlideObject& obj) { return obj.name == name; });

    if (it != objects.end() && it != objects.begin()) {
        SlideObject obj = std::move(*it);
        objects.erase(it);
        objects.insert(objects.begin(), std::move(obj));
        return true;
    }
    return false;
}

bool Slide::hasOverlaps() const
{
    for (size_t i = 0; i < objects.size(); ++i) {
        for (size_t j = i + 1; j < objects.size(); ++j) {
            if (objects[i].intersects(objects[j])) {
                return true;
            }
        }
    }
    return false;
}

std::vector<std::pair<std::string, std::string>> Slide::getOverlaps() const
{
    std::vector<std::pair<std::string, std::string>> overlaps;
    for (size_t i = 0; i < objects.size(); ++i) {
        for (size_t j = i + 1; j < objects.size(); ++j) {
            if (objects[i].intersects(objects[j])) {
                overlaps.emplace_back(objects[i].name, objects[j].name);
            }
        }
    }
    return overlaps;
}

void Slide::display() const
{
    std::cout << "Slide #" << id << " (" << text << ")\n";

    if (objects.empty()) {
        std::cout << "  (empty)\n";
    }
    else {
        std::cout << "  Objects (" << objects.size() << "):\n";
        for (const auto& obj : objects) {
            std::cout << "    ";
            obj.draw();
        }
    }
}

size_t Slide::size() const { return objects.size(); }