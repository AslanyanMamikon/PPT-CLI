#ifndef COMMAND_FACTORY_H_
#define COMMAND_FACTORY_H_

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "ICommand.h"

class CommandFactory {
public:
    static std::unique_ptr<ICommand> createCommand(
        const std::string& cmd,
        const std::string& object,
        const std::unordered_map<std::string, std::string>& flags,
        const std::vector<std::string>& args);
};

#endif // COMMAND_FACTORY_H_