#ifndef COMMAND_REGISTRY_H_
#define COMMAND_REGISTRY_H_

#include "IMetaCommand.h"
#include "ICommand.h"
#include "Editor.h"
#include <memory>
#include <unordered_map>
#include <vector>
#include <algorithm>

class CommandRegistry {
private:
    std::unordered_map<std::string, std::shared_ptr<IMetaCommand>> commands;

public:
    CommandRegistry();
    ~CommandRegistry() = default;

    // Register a command with its metadata
    void registerCommand(std::shared_ptr<IMetaCommand> metaCmd);

    // Find a metacommand by name
    std::shared_ptr<IMetaCommand> findMetaCommand(const std::string& name) const;

    // Get all registered metacommands
    std::vector<std::shared_ptr<IMetaCommand>> getAllMetaCommands() const;

    // Create a command instance from the registry
    std::unique_ptr<ICommand> createCommand(
        const std::string& cmdName,
        const std::string& object,
        const std::unordered_map<std::string, std::string>& flags,
        const std::vector<std::string>& args,
        bool* exitFlag = nullptr,
        Editor* editor = nullptr) const;

    bool hasCommand(const std::string& name) const;
    size_t size() const;

private:
    void registerAllCommands();
};

#endif // COMMAND_REGISTRY_H_