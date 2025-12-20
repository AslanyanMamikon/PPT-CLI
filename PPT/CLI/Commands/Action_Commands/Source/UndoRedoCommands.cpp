#include "UndoRedoCommands.h"

void UndoCommand::execute(Presentation& presentation) {
    editor.undo();
}

std::string UndoCommand::getName() const {
    return "undo";
}

void RedoCommand::execute(Presentation& presentation) {
    editor.redo();
}

std::string RedoCommand::getName() const {
    return "redo";
}