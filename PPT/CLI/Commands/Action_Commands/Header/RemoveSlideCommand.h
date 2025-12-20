#ifndef REMOVE_SLIDE_COMMAND_H_
#define REMOVE_SLIDE_COMMAND_H_

#include "ICommand.h"
#include "Editor.h"
#include "SlideActions.h"
#include "Argument.h"
#include <vector>
#include <unordered_map>
#include <iostream>

class RemoveSlideCommand : public ICommand {
private:
    std::string object;
    std::unordered_map<std::string, std::string> flags;
    std::vector<std::string> args;
    Editor& editor;

public:
    RemoveSlideCommand(const std::string& obj,
        const std::unordered_map<std::string, std::string>& f,
        const std::vector<std::string>& a,
        Editor& ed)
        : object(obj), flags(f), args(a), editor(ed) {
    }

    void execute(Presentation& presentation) override;
    std::string getName() const override;

protected:
    void validate() const override;
};

#endif // REMOVE_SLIDE_COMMAND_H_