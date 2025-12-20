#include "JSONSerializer.h"
#include <iostream>

bool JSONSerializer::saveToFile(const Presentation& presentation, const std::string& filename) {
    try {
        json j = serializePresentation(presentation);
        std::ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        file << j.dump(4);
        file.close();
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Save error: " << e.what() << "\n";
        return false;
    }
}

bool JSONSerializer::loadFromFile(Presentation& presentation, const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        json j;
        file >> j;
        file.close();

        deserializePresentation(presentation, j);
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Load error: " << e.what() << "\n";
        return false;
    }
}

json JSONSerializer::serializePresentation(const Presentation& presentation) {
    json j;
    j["slideCount"] = presentation.size();
    j["slides"] = json::array();

    Presentation& pres = const_cast<Presentation&>(presentation);

    for (size_t i = 0; i < presentation.size(); ++i) {
        Slide* slide = pres.getSlideAtPosition(static_cast<int>(i + 1));
        if (slide) {
            j["slides"].push_back(serializeSlide(*slide));
        }
    }

    return j;
}

json JSONSerializer::serializeSlide(const Slide& slide) {
    json j;
    j["id"] = slide.getId();
    j["text"] = slide.getText();
    j["objects"] = json::array();

    for (const auto& obj : slide.getObjects()) {
        j["objects"].push_back(serializeSlideObject(obj.get()));
    }

    return j;
}

json JSONSerializer::serializeSlideObject(const SlideObject* obj) {
    json j;
    j["type"] = obj->getType();
    j["name"] = obj->getName();
    j["geometry"] = serializeGeometry(obj->getGeometry());

    // Type-specific serialization
    if (obj->getType() == "Rectangle") {
        const Rectangle* rect = dynamic_cast<const Rectangle*>(obj);
        if (rect) {
            j["fillColor"] = rect->getFillColor();
            j["borderColor"] = rect->getBorderColor();
            j["borderWidth"] = rect->getBorderWidth();
        }
    }
    else if (obj->getType() == "Circle") {
        const Circle* circle = dynamic_cast<const Circle*>(obj);
        if (circle) {
            j["fillColor"] = circle->getFillColor();
            j["borderColor"] = circle->getBorderColor();
            j["borderWidth"] = circle->getBorderWidth();
        }
    }
    else if (obj->getType() == "Text") {
        const TextObject* text = dynamic_cast<const TextObject*>(obj);
        if (text) {
            j["content"] = text->getContent();
            j["font"] = text->getFont();
            j["fontSize"] = text->getFontSize();
            j["color"] = text->getColor();
            j["alignment"] = text->getAlignment();
        }
    }
    else if (obj->getType() == "Line") {
        const Line* line = dynamic_cast<const Line*>(obj);
        if (line) {
            j["x1"] = line->getStartX();
            j["y1"] = line->getStartY();
            j["x2"] = line->getEndX();
            j["y2"] = line->getEndY();
            j["color"] = line->getColor();
            j["width"] = line->getWidth();
        }
    }

    return j;
}

json JSONSerializer::serializeGeometry(const Geometry& geom) {
    json j;
    j["topLeft"] = { {"x", geom.getTopLeft().x}, {"y", geom.getTopLeft().y} };
    j["bottomRight"] = { {"x", geom.getBottomRight().x}, {"y", geom.getBottomRight().y} };
    return j;
}

void JSONSerializer::deserializePresentation(Presentation& presentation, const json& j) {
    // Clear existing slides
    while (presentation.size() > 0) {
        presentation.removeLastSlide();
    }

    if (j.contains("slides") && j["slides"].is_array()) {
        for (const auto& slideJson : j["slides"]) {
            auto slide = deserializeSlide(slideJson);
            if (slide) {
                std::string text = slideJson.value("text", "blank");
                Slide& newSlide = presentation.addSlide(text);

                // Copy objects from deserialized slide
                for (const auto& obj : slide->getObjects()) {
                    newSlide.addObject(obj->clone());
                }
            }
        }
    }
}

std::unique_ptr<Slide> JSONSerializer::deserializeSlide(const json& j) {
    int id = j.value("id", 1);
    std::string text = j.value("text", "blank");

    auto slide = std::make_unique<Slide>(id, text);

    if (j.contains("objects") && j["objects"].is_array()) {
        for (const auto& objJson : j["objects"]) {
            auto obj = deserializeSlideObject(objJson);
            if (obj) {
                slide->addObject(std::move(obj));
            }
        }
    }

    return slide;
}

std::unique_ptr<SlideObject> JSONSerializer::deserializeSlideObject(const json& j) {
    std::string type = j.value("type", "");
    std::string name = j.value("name", "");
    Geometry geom = deserializeGeometry(j["geometry"]);

    if (type == "Rectangle") {
        std::string fillColor = j.value("fillColor", "white");
        std::string borderColor = j.value("borderColor", "black");
        size_t borderWidth = j.value("borderWidth", 1);
        return std::make_unique<Rectangle>(name, geom, fillColor, borderColor, borderWidth);
    }
    else if (type == "Circle") {
        size_t centerX = geom.getCenterX();
        size_t centerY = geom.getCenterY();
        size_t radius = geom.getWidth() / 2;
        std::string fillColor = j.value("fillColor", "white");
        std::string borderColor = j.value("borderColor", "black");
        size_t borderWidth = j.value("borderWidth", 1);
        return std::make_unique<Circle>(name, centerX, centerY, radius, fillColor, borderColor, borderWidth);
    }
    else if (type == "Text") {
        std::string content = j.value("content", "");
        std::string font = j.value("font", "Arial");
        size_t fontSize = j.value("fontSize", 12);
        std::string color = j.value("color", "black");
        std::string alignment = j.value("alignment", "left");

        Point tl = geom.getTopLeft();
        auto text = std::make_unique<TextObject>(
            name,
            tl.x, tl.y,
            geom.getWidth(), geom.getHeight(),
            content, font, fontSize, color
        );
        text->setAlignment(alignment);
        return text;
    }
    else if (type == "Line") {
        size_t x1 = j.value("x1", geom.getTopLeft().x);
        size_t y1 = j.value("y1", geom.getTopLeft().y);
        size_t x2 = j.value("x2", geom.getBottomRight().x);
        size_t y2 = j.value("y2", geom.getBottomRight().y);
        std::string color = j.value("color", "black");
        size_t width = j.value("width", 1);
        return std::make_unique<Line>(name, x1, y1, x2, y2, color, width);
    }

    return nullptr;
}

Geometry JSONSerializer::deserializeGeometry(const json& j) {
    size_t x1 = j["topLeft"].value("x", 0);
    size_t y1 = j["topLeft"].value("y", 0);
    size_t x2 = j["bottomRight"].value("x", 0);
    size_t y2 = j["bottomRight"].value("y", 0);

    return Geometry(x1, y1, x2, y2);
}