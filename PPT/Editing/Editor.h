#ifndef EDITOR_H_
#define EDITOR_H_

#include "IAction.h"
#include "Presentation.h"
#include <deque>
#include <memory>
#include <iostream>

class Editor {
private:
    Presentation presentation;
    std::deque<std::unique_ptr<IAction>> undoStack;
    std::deque<std::unique_ptr<IAction>> redoStack;
    static constexpr size_t MAX_HISTORY_SIZE = 100;

public:
    Editor() = default;

    void doAction(std::unique_ptr<IAction> action);
    bool undo();
    bool redo();

    bool canUndo() const;
    bool canRedo() const;

    void clearHistory();

    Presentation& getPresentation();
    const Presentation& getPresentation() const;

    size_t undoSize() const;
    size_t redoSize() const;
};

#endif // EDITOR_H_