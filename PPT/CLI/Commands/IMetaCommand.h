#ifndef IMETA_COMMAND_H_
#define IMETA_COMMAND_H_

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class ICommand;
class Editor;

// Simple argument info for help display
struct MetaArgumentInfo {
    std::string name;
    bool required;
    std::string defaultValue;

    MetaArgumentInfo(const std::string& n = "", bool req = false, const std::string& defVal = "")
        : name(n), required(req), defaultValue(defVal) {
    }
};

// Interface for command metadata
class IMetaCommand {
public:
    virtual ~IMetaCommand() = default;

    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual const std::vector<MetaArgumentInfo>& getArguments() const = 0;

    // Factory method to create the actual command
    virtual std::unique_ptr<ICommand> createCommand(
        const std::string& object,
        const std::unordered_map<std::string, std::string>& flags,
        const std::vector<std::string>& args,
        bool* exitFlag,
        Editor* editor) const = 0;
};

// Function pointer type for command creation
using CommandCreator = std::unique_ptr<ICommand>(*)(
    const std::string&,
    const std::unordered_map<std::string, std::string>&,
    const std::vector<std::string>&,
    bool*,
    Editor*);

// Concrete implementation of command metadata
class MetaCommand : public IMetaCommand {
private:
    std::string name;
    std::string description;
    std::vector<MetaArgumentInfo> arguments;
    CommandCreator creator;

public:
    MetaCommand(const std::string& name,
        const std::string& description,
        CommandCreator creator)
        : name(name), description(description), creator(creator) {
    }

    std::string getName() const override {
        return name;
    }

    std::string getDescription() const override {
        return description;
    }

    const std::vector<MetaArgumentInfo>& getArguments() const override {
        return arguments;
    }

    void addArgument(const MetaArgumentInfo& arg) {
        arguments.push_back(arg);
    }

    std::unique_ptr<ICommand> createCommand(
        const std::string& object,
        const std::unordered_map<std::string, std::string>& flags,
        const std::vector<std::string>& args,
        bool* exitFlag,
        Editor* editor) const override {

        if (creator) {
            return creator(object, flags, args, exitFlag, editor);
        }
        return nullptr;
    }
};

#endif // IMETA_COMMAND_H_