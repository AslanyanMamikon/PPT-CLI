#include "AddShapeCommand.h"
#include "Rectangle.h"
#include "Circle.h"
#include "TextObject.h"
#include "Line.h"

void AddShapeCommand::execute(Presentation& presentation) {
    validate();

    int slidePos = 1;
    if (auto it = flags.find("-slide"); it != flags.end())
        slidePos = std::stoi(it->second);

    auto shape = createShape();

    auto action = std::make_unique<AddShapeAction>(slidePos, std::move(shape));

    editor.doAction(std::move(action));
}

std::string AddShapeCommand::getName() const {
    return "add shape";
}

void AddShapeCommand::validate() const {
    if (object != "rectangle" && object != "circle" &&
        object != "text" && object != "line") {
        throw CommandValidationException(
            "Add shape supports: rectangle, circle, text, line");
    }

    ArgumentValidator validator;
    validator.addInfo({ "-name", ArgumentType::String, true, {} });
    validator.addInfo({ "-slide", ArgumentType::Integer, false, {} });
    validator.addInfo({ "-x", ArgumentType::Integer, true, {} });
    validator.addInfo({ "-y", ArgumentType::Integer, true, {} });

    if (object == "rectangle" || object == "text") {
        validator.addInfo({ "-width", ArgumentType::Integer, true, {} });
        validator.addInfo({ "-height", ArgumentType::Integer, true, {} });
    }
    else if (object == "circle") {
        validator.addInfo({ "-radius", ArgumentType::Integer, true, {} });
    }
    else if (object == "line") {
        validator.addInfo({ "-x2", ArgumentType::Integer, true, {} });
        validator.addInfo({ "-y2", ArgumentType::Integer, true, {} });
    }

    validator.addInfo({ "-fill", ArgumentType::String, false, {} });
    validator.addInfo({ "-border", ArgumentType::String, false, {} });
    validator.addInfo({ "-border-width", ArgumentType::Integer, false, {} });
    validator.addInfo({ "-content", ArgumentType::String, false, {} });
    validator.addInfo({ "-font", ArgumentType::String, false, {} });
    validator.addInfo({ "-font-size", ArgumentType::Integer, false, {} });
    validator.addInfo({ "-color", ArgumentType::String, false, {} });
    validator.addInfo({ "-width", ArgumentType::Integer, false, {} });

    validator.validate(flags);
}

std::unique_ptr<SlideObject> AddShapeCommand::createShape() {
    std::string name = flags.at("-name");
    size_t x = std::stoi(flags.at("-x"));
    size_t y = std::stoi(flags.at("-y"));

    if (object == "rectangle") {
        size_t width = std::stoi(flags.at("-width"));
        size_t height = std::stoi(flags.at("-height"));
        std::string fill = getFlag("-fill", "white");
        std::string border = getFlag("-border", "black");
        size_t borderWidth = std::stoi(getFlag("-border-width", "1"));

        return std::make_unique<Rectangle>(name, x, y, width, height,
            fill, border, borderWidth);
    }
    else if (object == "circle") {
        size_t radius = std::stoi(flags.at("-radius"));
        std::string fill = getFlag("-fill", "white");
        std::string border = getFlag("-border", "black");
        size_t borderWidth = std::stoi(getFlag("-border-width", "1"));

        return std::make_unique<Circle>(name, x, y, radius,
            fill, border, borderWidth);
    }
    else if (object == "text") {
        size_t width = std::stoi(flags.at("-width"));
        size_t height = std::stoi(flags.at("-height"));
        std::string content = getFlag("-content", "");
        std::string font = getFlag("-font", "Arial");
        size_t fontSize = std::stoi(getFlag("-font-size", "12"));
        std::string color = getFlag("-color", "black");

        return std::make_unique<TextObject>(name, x, y, width, height,
            content, font, fontSize, color);
    }
    else if (object == "line") {
        size_t x2 = std::stoi(flags.at("-x2"));
        size_t y2 = std::stoi(flags.at("-y2"));
        std::string color = getFlag("-color", "black");
        size_t width = std::stoi(getFlag("-width", "1"));

        return std::make_unique<Line>(name, x, y, x2, y2, color, width);
    }

    throw CommandValidationException("Unknown shape type: " + object);
}

std::string AddShapeCommand::getFlag(const std::string& flagName,
    const std::string& defaultValue) const {
    auto it = flags.find(flagName);
    return (it != flags.end()) ? it->second : defaultValue;
}