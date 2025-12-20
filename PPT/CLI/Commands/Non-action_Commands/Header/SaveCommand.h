#ifndef SAVE_COMMAND_H_
#define SAVE_COMMAND_H_

#include "ICommand.h"
#include "Argument.h"
#include "Presentation.h"
#include "JSONSerializer.h"
#include <vector>
#include <unordered_map>
#include <iostream>

class SaveCommand : public ICommand
{
private:
    std::string object;
    std::unordered_map<std::string, std::string> flags;
    std::vector<std::string> args;

public:
    SaveCommand(const std::string& obj,
        const std::unordered_map<std::string, std::string>& f,
        const std::vector<std::string>& a);

    void execute(Presentation& presentation) override;
    std::string getName() const override;

protected:
    void validate() const override;
};

class LoadCommand : public ICommand
{
private:
    std::string object;
    std::unordered_map<std::string, std::string> flags;
    std::vector<std::string> args;

public:
    LoadCommand(const std::string& obj,
        const std::unordered_map<std::string, std::string>& f,
        const std::vector<std::string>& a);

    void execute(Presentation& presentation) override;
    std::string getName() const override;

protected:
    void validate() const override;
};

#endif // SAVE_COMMAND_H_