#include "CommandFactory.h"
#include "AddCommand.h"
#include "RemoveCommand.h"
#include "ListCommand.h"

std::unique_ptr<ICommand> CommandFactory::createCommand(
    const std::string& cmd,
    const std::string& object,
    const std::unordered_map<std::string, std::string>& flags,
    const std::vector<std::string>& args) {

    if (cmd == "add" && object == "slide") {
        return std::make_unique<AddSlideCommand>(object, flags, args);
    }
    else if (cmd == "remove" && object == "slide") {
        return std::make_unique<RemoveSlideCommand>(object, flags, args);
    }
    else if (cmd == "list" && (object == "slides" || object == "slide" || object.empty())) {
        return std::make_unique<ListSlidesCommand>(object, flags, args);
    }

    throw CommandValidationException("Unknown command: " + cmd);
}
