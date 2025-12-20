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

    void execute(Presentation& presentation) override;

    std::string getName() const override;

protected:
    void validate() const override;
};

#endif // !LIST_COMMAND_H_
