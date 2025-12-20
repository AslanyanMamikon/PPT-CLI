#include "MoveSlideCommand.h"

void MoveSlideCommand::execute(Presentation& presentation) {
    validate();

    int fromPos = std::stoi(flags.at("-from"));
    int toPos = std::stoi(flags.at("-to"));

    auto action = std::make_unique<MoveSlideAction>(fromPos, toPos);

    editor.doAction(std::move(action));
}

std::string MoveSlideCommand::getName() const {
    return "move slide";
}

void MoveSlideCommand::validate() const {
    if (object != "slide") {
        throw CommandValidationException("Move command supports only: slide");
    }

    ArgumentValidator validator;
    validator.addInfo({ "-from", ArgumentType::Integer, true, {} });
    validator.addInfo({ "-to", ArgumentType::Integer, true, {} });
    validator.validate(flags);
}