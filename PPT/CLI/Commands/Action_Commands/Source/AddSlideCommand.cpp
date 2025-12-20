#include "AddSlideCommand.h"

void AddSlideCommand::execute(Presentation& presentation) {
    validate();

    std::string text = "blank";
    if (auto it = flags.find("-text"); it != flags.end())
        text = it->second;

    int position = -1; // -1 means add at end
    if (auto it = flags.find("-pos"); it != flags.end())
        position = std::stoi(it->second);

    auto action = std::make_unique<AddSlideAction>(position, text);

    editor.doAction(std::move(action));
}

std::string AddSlideCommand::getName() const {
    return "add slide";
}

void AddSlideCommand::validate() const {
    if (object != "slide") {
        throw CommandValidationException("Add command supports only: slide");
    }

    ArgumentValidator validator;
    validator.addInfo({ "-text", ArgumentType::Enum, false,
        {"title", "blank", "content"} });
    validator.addInfo({ "-pos", ArgumentType::Integer, false, {} });
    validator.validate(flags);
}