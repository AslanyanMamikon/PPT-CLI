#include "JSONSerializer.h"

bool JSONSerializer::saveToFile(const Presentation& presentation, const std::string& filename)
{
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

bool JSONSerializer::loadFromFile(Presentation& presentation, const std::string& filename)
{
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

json JSONSerializer::serializePresentation(const Presentation& presentation)
{
    json j;
    j["slideCount"] = presentation.size();
    j["slides"] = json::array();

    // Need to access slides - requires adding const getter to Presentation
    // For now, cast away const (not ideal but functional)
    Presentation& pres = const_cast<Presentation&>(presentation);

    for (size_t i = 0; i < presentation.size(); ++i) {
        Slide* slide = pres.getSlideAtPosition(static_cast<int>(i + 1));
        if (slide) {
            j["slides"].push_back(serializeSlide(*slide));
        }
    }

    return j;
}

json JSONSerializer::serializeSlide(const Slide& slide)
{
    json j;
    j["id"] = slide.getId();
    j["text"] = slide.getText();
    j["objects"] = json::array();

    for (const auto& obj : slide.getObjects()) {
        j["objects"].push_back(serializeSlideObject(obj));
    }

    return j;
}

json JSONSerializer::serializeSlideObject(const SlideObject& obj)
{
    json j;
    j["type"] = static_cast<int>(obj.type);
    j["name"] = obj.name;
    j["color"] = obj.color;
    j["fontSize"] = obj.fontSize;
    j["pos"] = { {"x", obj.pos.x}, {"y", obj.pos.y} };
    j["size"] = { {"width", obj.size.width}, {"height", obj.size.height} };

    if (obj.shape) {
        j["shape"] = serializeShape(obj.shape.get());
    }

    return j;
}

json JSONSerializer::serializeShape(const IShape* shape)
{
    json j;
    j["type"] = shape->getType();
    j["name"] = shape->getName();
    j["fillColor"] = shape->getFillColor();
    j["borderColor"] = shape->getBorderColor();
    j["borderWidth"] = shape->getBorderWidth();
    j["bounds"] = serializeBoundingBox(shape->getBounds());

    // Store type-specific data
    if (shape->getType() == "Circle") {
        auto bounds = shape->getBounds();
        j["centerX"] = bounds.getCenterX();
        j["centerY"] = bounds.getCenterY();
        j["radius"] = bounds.getWidth() / 2;
    }
    else if (shape->getType() == "Text") {
        const TextShape* text = dynamic_cast<const TextShape*>(shape);
        if (text) {
            j["content"] = text->getContent();
            j["font"] = text->getFont();
            j["fontSize"] = text->getFontSize();
            j["alignment"] = text->getAlignment();
        }
    }
    else if (shape->getType() == "Line") {
        const Line* line = dynamic_cast<const Line*>(shape);
        if (line) {
            j["x1"] = line->getStartX();
            j["y1"] = line->getStartY();
            j["x2"] = line->getEndX();
            j["y2"] = line->getEndY();
        }
    }

    return j;
}

json JSONSerializer::serializeBoundingBox(const BoundingBox& bounds)
{
    json j;
    j["topLeft"] = { {"x", bounds.getTopLeft().x}, {"y", bounds.getTopLeft().y} };
    j["bottomRight"] = { {"x", bounds.getBottomRight().x}, {"y", bounds.getBottomRight().y} };
    return j;
}

void JSONSerializer::deserializePresentation(Presentation& presentation, const json& j)
{
    // Clear existing slides
    while (presentation.size() > 0) {
        presentation.removeLastSlide();
    }

    if (j.contains("slides") && j["slides"].is_array()) {
        for (const auto& slideJson : j["slides"]) {
            auto slide = deserializeSlide(slideJson);
            if (slide) {
                // Add slide with text
                std::string text = slideJson.value("text", "blank");
                Slide& newSlide = presentation.addSlide(text);

                // Copy objects from deserialized slide
                for (const auto& obj : slide->getObjects()) {
                    if (obj.shape) {
                        auto clonedShape = obj.shape->clone();
                        SlideObject newObj(obj.type, obj.name, std::move(clonedShape));
                        newObj.color = obj.color;
                        newObj.fontSize = obj.fontSize;
                        newObj.pos = obj.pos;
                        newObj.size = obj.size;
                        newSlide.addObject(std::move(newObj));
                    }
                }
            }
        }
    }
}

std::unique_ptr<Slide> JSONSerializer::deserializeSlide(const json& j)
{
    int id = j.value("id", 1);
    std::string text = j.value("text", "blank");

    auto slide = std::make_unique<Slide>(id, text);

    if (j.contains("objects") && j["objects"].is_array()) {
        for (const auto& objJson : j["objects"]) {
            SlideObject obj = deserializeSlideObject(objJson);
            slide->addObject(std::move(obj));
        }
    }

    return slide;
}

SlideObject JSONSerializer::deserializeSlideObject(const json& j)
{
    ObjectType type = static_cast<ObjectType>(j.value("type", 0));
    std::string name = j.value("name", "");

    std::unique_ptr<IShape> shape;
    if (j.contains("shape")) {
        shape = deserializeShape(j["shape"]);
    }

    SlideObject obj(type, name, std::move(shape));
    obj.color = j.value("color", "");
    obj.fontSize = j.value("fontSize", 12);

    if (j.contains("pos")) {
        obj.pos.x = j["pos"].value("x", 0);
        obj.pos.y = j["pos"].value("y", 0);
    }

    if (j.contains("size")) {
        obj.size.width = j["size"].value("width", 0);
        obj.size.height = j["size"].value("height", 0);
    }

    return obj;
}

std::unique_ptr<IShape> JSONSerializer::deserializeShape(const json& j)
{
    std::string type = j.value("type", "");
    std::string name = j.value("name", "");
    std::string fillColor = j.value("fillColor", "white");
    std::string borderColor = j.value("borderColor", "black");
    size_t borderWidth = j.value("borderWidth", 1);

    BoundingBox bounds = deserializeBoundingBox(j["bounds"]);

    if (type == "Rectangle") {
        return std::make_unique<Rectangle>(name, bounds, fillColor, borderColor, borderWidth);
    }
    else if (type == "Circle") {
        size_t centerX = j.value("centerX", bounds.getCenterX());
        size_t centerY = j.value("centerY", bounds.getCenterY());
        size_t radius = j.value("radius", bounds.getWidth() / 2);
        return std::make_unique<Circle>(name, centerX, centerY, radius, fillColor, borderColor, borderWidth);
    }
    else if (type == "Text") {
        std::string content = j.value("content", "");
        std::string font = j.value("font", "Arial");
        size_t fontSize = j.value("fontSize", 12);
        std::string alignment = j.value("alignment", "left");

        auto text = std::make_unique<TextShape>(
            name,
            bounds.getTopLeft().x,
            bounds.getTopLeft().y,
            bounds.getWidth(),
            bounds.getHeight(),
            content,
            font,
            fontSize,
            fillColor
        );
        text->setAlignment(alignment);
        return text;
    }
    else if (type == "Line") {
        size_t x1 = j.value("x1", bounds.getTopLeft().x);
        size_t y1 = j.value("y1", bounds.getTopLeft().y);
        size_t x2 = j.value("x2", bounds.getBottomRight().x);
        size_t y2 = j.value("y2", bounds.getBottomRight().y);
        return std::make_unique<Line>(name, x1, y1, x2, y2, borderColor, borderWidth);
    }

    return nullptr;
}

BoundingBox JSONSerializer::deserializeBoundingBox(const json& j)
{
    size_t x1 = j["topLeft"].value("x", 0);
    size_t y1 = j["topLeft"].value("y", 0);
    size_t x2 = j["bottomRight"].value("x", 0);
    size_t y2 = j["bottomRight"].value("y", 0);

    return BoundingBox(x1, y1, x2, y2);
}