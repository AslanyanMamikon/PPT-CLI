#ifndef UNDO_REDO_COMMANDS_H_
#define UNDO_REDO_COMMANDS_H_

#include "ICommand.h"
#include "Editor.h"
#include "Presentation.h"
#include <iostream>

class UndoCommand : public ICommand {
private:
    Editor& editor;

public:
    explicit UndoCommand(Editor& ed) : editor(ed) {}

    void execute(Presentation& presentation) override;
    std::string getName() const override;

protected:
    void validate() const override {
        // No validation needed
    }
};

class RedoCommand : public ICommand {
private:
    Editor& editor;

public:
    explicit RedoCommand(Editor& ed) : editor(ed) {}

    void execute(Presentation& presentation) override;
    std::string getName() const override;

protected:
    void validate() const override {
        // No validation needed
    }
};

#endif // UNDO_REDO_COMMANDS_H_