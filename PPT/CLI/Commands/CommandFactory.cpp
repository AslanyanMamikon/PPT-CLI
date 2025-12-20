#include "CommandFactory.h"
#include "AddSlideCommand.h"
#include "RemoveSlideCommand.h"
#include "MoveSlideCommand.h"
#include "AddShapeCommand.h"
#include "RemoveShapeCommand.h"
#include "UndoRedoCommands.h"
#include "ListCommand.h"
#include "DuplicateCommand.h"
#include "ExitCommand.h"
#include "SaveCommand.h"
#include "RenderCommand.h"

std::unique_ptr<ICommand> CommandFactory::createCommand(
    const std::string& cmd,
    const std::string& object,
    const std::unordered_map<std::string, std::string>& flags,
    const std::vector<std::string>& args,
    bool* exitFlag,
    Editor* editor)
{
    // Undo/Redo commands (require editor)
    if (cmd == "undo") {
        if (!editor) {
            throw CommandValidationException("Undo requires editor reference");
        }
        return std::make_unique<UndoCommand>(*editor);
    }
    else if (cmd == "redo") {
        if (!editor) {
            throw CommandValidationException("Redo requires editor reference");
        }
        return std::make_unique<RedoCommand>(*editor);
    }

    // Exit command
    if (cmd == "exit" || cmd == "quit") {
        if (!exitFlag) {
            throw CommandValidationException("Exit command requires exit flag reference");
        }
        return std::make_unique<ExitCommand>(object, flags, args, *exitFlag);
    }

    // Action-based commands
    if (editor) {
        if (cmd == "add" && object == "slide") {
            return std::make_unique<AddSlideCommand>(object, flags, args, *editor);
        }
        else if (cmd == "remove" && object == "slide") {
            return std::make_unique<RemoveSlideCommand>(object, flags, args, *editor);
        }
        else if (cmd == "move" && object == "slide") {
            return std::make_unique<MoveSlideCommand>(object, flags, args, *editor);
        }
        else if (cmd == "add" && (object == "rectangle" || object == "circle" ||
            object == "text" || object == "line")) {
            return std::make_unique<AddShapeCommand>(object, flags, args, *editor);
        }
        else if (cmd == "remove" && (object == "rectangle" || object == "circle" ||
            object == "text" || object == "line" || object == "shape")) {
            return std::make_unique<RemoveShapeCommand>(object, flags, args, *editor);
        }
    }

    // Non-action commands
    if (cmd == "list" && (object == "slides" || object == "slide" || object.empty())) {
        return std::make_unique<ListSlidesCommand>(object, flags, args);
    }
    else if (cmd == "duplicate" && object == "slide") {
        return std::make_unique<DuplicateSlideCommand>(object, flags, args);
    }
    else if (cmd == "save") {
        return std::make_unique<SaveCommand>(object, flags, args);
    }
    else if (cmd == "load") {
        return std::make_unique<LoadCommand>(object, flags, args);
    }
    else if (cmd == "render" && object == "slide") {
        return std::make_unique<RenderSlideCommand>(object, flags, args);
    }
    else if (cmd == "render" && (object == "presentation" || object == "all" || object.empty())) {
        return std::make_unique<RenderPresentationCommand>(object, flags, args);
    }
    else if (cmd == "show" && object == "slide") {
        return std::make_unique<ShowSlideCommand>(object, flags, args);
    }

    // Unknown command
    throw CommandValidationException("Unknown command: " + cmd);
}