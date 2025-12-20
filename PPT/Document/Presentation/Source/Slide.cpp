#include "Slide.h"

Slide::Slide(int id, std::string layout)
    : id(id), layoutType(std::move(layout)) {
}

Slide::Slide(const Slide& other)
    : id(other.id), layoutType(other.layoutType) {
    for (const auto& obj : other.objects) {
        objects.push_back(obj->clone());
    }
}

int Slide::getId() const {
    return id;
}

void Slide::setId(int newId) {
    id = newId;
}

const std::string& Slide::getText() const {
    return layoutType;
}

void Slide::addObject(std::unique_ptr<SlideObject> obj) {
    if (hasObject(obj->getName())) {
        throw std::runtime_error("Object '" + obj->getName() + "' already exists");
    }
    objects.push_back(std::move(obj));
}

SlideObject* Slide::getObject(const std::string& name) {
    auto it = std::find_if(objects.begin(), objects.end(),
        [&name](const auto& obj) { return obj->getName() == name; });
    return it != objects.end() ? it->get() : nullptr;
}

const SlideObject* Slide::getObject(const std::string& name) const {
    auto it = std::find_if(objects.begin(), objects.end(),
        [&name](const auto& obj) { return obj->getName() == name; });
    return it != objects.end() ? it->get() : nullptr;
}

SlideObject* Slide::getObjectAt(size_t x, size_t y) {
    for (auto it = objects.rbegin(); it != objects.rend(); ++it) {
        if (GeometryUtils::contains((*it)->getGeometry(), x, y)) {
            return it->get();
        }
    }
    return nullptr;
}

bool Slide::hasObject(const std::string& name) const {
    return std::any_of(objects.begin(), objects.end(),
        [&name](const auto& obj) { return obj->getName() == name; });
}

const std::vector<std::unique_ptr<SlideObject>>& Slide::getObjects() const {
    return objects;
}

bool Slide::moveObject(const std::string& name, size_t deltaX, size_t deltaY) {
    SlideObject* obj = getObject(name);
    if (obj) {
        Geometry newGeom = GeometryUtils::move(obj->getGeometry(), deltaX, deltaY);
        obj->setGeometry(newGeom);
        return true;
    }
    return false;
}

bool Slide::resizeObject(const std::string& name, size_t newWidth, size_t newHeight) {
    SlideObject* obj = getObject(name);
    if (obj) {
        Geometry newGeom = GeometryUtils::resize(obj->getGeometry(), newWidth, newHeight);
        obj->setGeometry(newGeom);
        return true;
    }
    return false;
}

bool Slide::bringToFront(const std::string& name) {
    auto it = std::find_if(objects.begin(), objects.end(),
        [&name](const auto& obj) { return obj->getName() == name; });

    if (it != objects.end() && it != objects.end() - 1) {
        auto obj = std::move(*it);
        objects.erase(it);
        objects.push_back(std::move(obj));
        return true;
    }
    return false;
}

bool Slide::sendToBack(const std::string& name) {
    auto it = std::find_if(objects.begin(), objects.end(),
        [&name](const auto& obj) { return obj->getName() == name; });

    if (it != objects.end() && it != objects.begin()) {
        auto obj = std::move(*it);
        objects.erase(it);
        objects.insert(objects.begin(), std::move(obj));
        return true;
    }
    return false;
}

bool Slide::hasOverlaps() const {
    for (size_t i = 0; i < objects.size(); ++i) {
        for (size_t j = i + 1; j < objects.size(); ++j) {
            if (GeometryUtils::intersects(objects[i]->getGeometry(),
                objects[j]->getGeometry())) {
                return true;
            }
        }
    }
    return false;
}

std::vector<std::pair<std::string, std::string>> Slide::getOverlaps() const {
    std::vector<std::pair<std::string, std::string>> overlaps;
    for (size_t i = 0; i < objects.size(); ++i) {
        for (size_t j = i + 1; j < objects.size(); ++j) {
            if (GeometryUtils::intersects(objects[i]->getGeometry(),
                objects[j]->getGeometry())) {
                overlaps.emplace_back(objects[i]->getName(), objects[j]->getName());
            }
        }
    }
    return overlaps;
}

void Slide::display() const {
    std::cout << "Slide #" << id << " (" << layoutType << ")\n";

    if (objects.empty()) {
        std::cout << "  (empty)\n";
    }
    else {
        std::cout << "  Objects (" << objects.size() << "):\n";
        for (const auto& obj : objects) {
            std::cout << "    ";
            obj->draw();
        }
    }
}

size_t Slide::size() const {
    return objects.size();
}

void Slide::renderToCanvas(ICanvas& canvas, const IPainter& painter) const {
    std::string bgColor = getBackgroundColor();
    canvas.setBackground(bgColor);

    for (const auto& obj : objects) {
        obj->paint(painter, canvas);
    }
}

std::string Slide::getBackgroundColor() const {
    if (layoutType == "title") {
        return "#f0f8ff"; 
    }
    else if (layoutType == "content") {
        return "#fffef0"; 
    }
    return "white";
}