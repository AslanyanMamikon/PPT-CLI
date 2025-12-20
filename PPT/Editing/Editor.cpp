#include "Editor.h"

void Editor::doAction(std::unique_ptr<IAction> action) {
    action->execute(presentation);

    std::unique_ptr<IAction> inverseAction = action->createInverse();

    redoStack.clear();

    undoStack.push_back(std::move(inverseAction));

    if (undoStack.size() > MAX_HISTORY_SIZE) {
        undoStack.pop_front();
    }
}

bool Editor::undo() {
    if (undoStack.empty()) {
        std::cout << "Nothing to undo\n";
        return false;
    }

    std::unique_ptr<IAction> inverseAction = std::move(undoStack.back());
    undoStack.pop_back();

    inverseAction->execute(presentation);

    std::unique_ptr<IAction> redoAction = inverseAction->createInverse();

    redoStack.push_back(std::move(redoAction));

    std::cout << "Undo successful\n";
    return true;
}

bool Editor::redo() {
    if (redoStack.empty()) {
        std::cout << "Nothing to redo\n";
        return false;
    }

    std::unique_ptr<IAction> action = std::move(redoStack.back());
    redoStack.pop_back();

    action->execute(presentation);

    std::unique_ptr<IAction> inverseAction = action->createInverse();

    undoStack.push_back(std::move(inverseAction));

    std::cout << "Redo successful\n";
    return true;
}

bool Editor::canUndo() const {
    return !undoStack.empty();
}

bool Editor::canRedo() const {
    return !redoStack.empty();
}

void Editor::clearHistory() {
    undoStack.clear();
    redoStack.clear();
}

Presentation& Editor::getPresentation() {
    return presentation;
}

const Presentation& Editor::getPresentation() const {
    return presentation;
}

size_t Editor::undoSize() const {
    return undoStack.size();
}

size_t Editor::redoSize() const {
    return redoStack.size();
}