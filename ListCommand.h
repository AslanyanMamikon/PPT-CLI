#ifndef LIST_COMMAND_H_
#define LIST_COMMAND_H_

#include "ICommand.h"
#include "Argument.h"
#include "Presentation.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <sstream>

class ListSlidesCommand : public ICommand {
private:
    std::string object;
    std::unordered_map<std::string, std::string> flags;
    std::vector<std::string> args;

public:
    ListSlidesCommand(const std::string& obj,
        const std::unordered_map<std::string, std::string>& f,
        const std::vector<std::string>& a)
        : object(obj), flags(f), args(a)
    {
        //validate();
    }

    void execute(Presentation& presentation) override {
        validate();

        if (presentation.size() == 0)
            throw CommandValidationException("Presentation is empty. No slides to list.");

        presentation.listSlides();
    }

    std::string getName() const override { return "list"; }

protected:
    void validate() const {
        if (!object.empty() && object != "slides" && object != "slide") {
            throw CommandValidationException("List command only supports 'slides' or no object");
        }
    }
};

#endif // !LIST_COMMAND_H_
