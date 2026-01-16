#ifndef HELP_COMMAND_H_
#define HELP_COMMAND_H_

#include "ICommand.h"
#include "CommandRegistry.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

class HelpCommand : public ICommand {
private:
    CommandRegistry& registry;
    std::string specificCommand;

public:
    HelpCommand(CommandRegistry& reg, const std::string& specificCmd = "")
        : registry(reg), specificCommand(specificCmd) {}

    void execute(Presentation& presentation) override;
    std::string getName() const override;

protected:
    void validate() const override {
        // No validation needed for help command
    }

private:
    void showAllCommands();
    void showSpecificCommand(const std::string& cmdName);
};

#endif // HELP_COMMAND_H_