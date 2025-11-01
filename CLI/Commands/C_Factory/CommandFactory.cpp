#include "CommandFactory.h"
#include "AddCommand.h"
#include "RemoveCommand.h"
#include "ListCommand.h"
#include "MoveCommand.h"
#include "DuplicateCommand.h"
#include "AddShapeCommand.h"
#include "ExitCommand.h"
#include "SaveCommand.h"

std::unique_ptr<ICommand> CommandFactory::createCommand(
    const std::string& cmd,
    const std::string& object,
    const std::unordered_map<std::string, std::string>& flags,
    const std::vector<std::string>& args,
    bool* exitFlag) 
{
    if (cmd == "exit" || cmd == "quit") {
        if (!exitFlag) {
            throw CommandValidationException("Exit command requires exit flag reference");
        }
        return std::make_unique<ExitCommand>(object, flags, args, *exitFlag);
    }
    else if (cmd == "add" && object == "slide") {
        return std::make_unique<AddSlideCommand>(object, flags, args);
    }
    else if (cmd == "remove" && object == "slide") {
        return std::make_unique<RemoveSlideCommand>(object, flags, args);
    }
    else if (cmd == "list" && (object == "slides" || object == "slide" || object.empty())) {
        return std::make_unique<ListSlidesCommand>(object, flags, args);
    }
    else if (cmd == "move" && object == "slide") {
        return std::make_unique<MoveSlideCommand>(object, flags, args);
    }
    else if (cmd == "duplicate" && object == "slide") {
        return std::make_unique<DuplicateSlideCommand>(object, flags, args);
    }

    if(cmd == "add" && (object == "rectangle" || object == "circle" ||
                        object == "text" || object == "line")) {
        return std::make_unique<AddShapeCommand>(object, flags, args);
    }
    else if (cmd == "save") {
        return std::make_unique<SaveCommand>(object, flags, args);
    }
    else if (cmd == "load") {
        return std::make_unique<LoadCommand>(object, flags, args);
    }

    // If we reach here, the command is unknown
    throw CommandValidationException("Unknown command: " + cmd);
}