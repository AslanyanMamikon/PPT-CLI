#include "RemoveSlideCommand.h"

void RemoveSlideCommand::execute(Presentation& presentation) {
    validate();

    int position;
    if (auto it = flags.find("-pos"); it != flags.end()) {
        position = std::stoi(it->second);
    }
    else {
        position = static_cast<int>(presentation.size());
    }

    auto action = std::make_unique<RemoveSlideAction>(position);

    editor.doAction(std::move(action));
}

std::string RemoveSlideCommand::getName() const {
    return "remove slide";
}

void RemoveSlideCommand::validate() const {
    if (object != "slide") {
        throw CommandValidationException("Remove command supports only: slide");
    }

    ArgumentValidator validator;
    validator.addInfo({ "-pos", ArgumentType::Integer, false, {} });
    validator.validate(flags);
}