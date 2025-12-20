#include "RemoveShapeCommand.h"

void RemoveShapeCommand::execute(Presentation& presentation) {
    validate();

    std::string shapeName = flags.at("-name");

    int slidePos = 1;
    if (auto it = flags.find("-slide"); it != flags.end())
        slidePos = std::stoi(it->second);

    auto action = std::make_unique<RemoveShapeAction>(slidePos, shapeName);

    editor.doAction(std::move(action));
}

std::string RemoveShapeCommand::getName() const {
    return "remove shape";
}

void RemoveShapeCommand::validate() const {
    if (object != "rectangle" && object != "circle" &&
        object != "text" && object != "line" && object != "shape") {
        throw CommandValidationException(
            "Remove shape supports: rectangle, circle, text, line, shape");
    }

    ArgumentValidator validator;
    validator.addInfo({ "-name", ArgumentType::String, true, {} });
    validator.addInfo({ "-slide", ArgumentType::Integer, false, {} });
    validator.validate(flags);
}