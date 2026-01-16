
#include "HelpCommand.h"


void HelpCommand::execute(Presentation& presentation) {
    if (specificCommand.empty()) {
        showAllCommands();
    }
    else {
        showSpecificCommand(specificCommand);
    }
}

std::string HelpCommand::getName() const {
    return "help";
}

void HelpCommand::showAllCommands() {
    std::cout << "\n========================================\n";
    std::cout << "  Available Commands\n";
    std::cout << "========================================\n\n";

    auto metaCommands = registry.getAllMetaCommands();

    // Sort commands alphabetically
    std::sort(metaCommands.begin(), metaCommands.end(),
        [](const auto& a, const auto& b) {
            return a->getName() < b->getName();
        });

    // Find the longest command name for formatting
    size_t maxLength = 0;
    for (const auto& metaCmd : metaCommands) {
        maxLength = std::max(maxLength, metaCmd->getName().length());
    }

    for (const auto& metaCmd : metaCommands) {
        std::cout << "  " << std::left << std::setw(static_cast<int>(maxLength + 2))
            << metaCmd->getName() << " - "
            << metaCmd->getDescription() << "\n";
    }

    std::cout << "\n========================================\n";
    std::cout << "Use 'help <command>' for detailed information.\n";
    std::cout << "Examples: help add slide, help undo, help list\n";
    std::cout << "========================================\n\n";
}

void HelpCommand::showSpecificCommand(const std::string& cmdName) {
    // Try to find the command by exact name first
    auto metaCmd = registry.findMetaCommand(cmdName);

    // If not found, try to find commands that contain this name
    if (!metaCmd) {
        auto allCommands = registry.getAllMetaCommands();
        std::vector<std::shared_ptr<IMetaCommand>> matches;

        for (const auto& cmd : allCommands) {
            std::string cmdFullName = cmd->getName();
            // Check if the command name contains our search term
            if (cmdFullName.find(cmdName) != std::string::npos) {
                matches.push_back(cmd);
            }
        }

        if (matches.empty()) {
            std::cout << "\nError: Unknown command '" << cmdName << "'\n";
            std::cout << "Use 'help' to see all available commands.\n\n";
            return;
        }
        else if (matches.size() == 1) {
            // Found exactly one match
            metaCmd = matches[0];
        }
        else {
            // Multiple matches found
            std::cout << "\nMultiple commands match '" << cmdName << "':\n";
            for (const auto& match : matches) {
                std::cout << "  - " << match->getName() << "\n";
            }
            std::cout << "\nPlease be more specific. Use 'help <full command name>'\n";
            std::cout << "Example: help " << matches[0]->getName() << "\n\n";
            return;
        }
    }

    // Display the command details
    std::cout << "\n========================================\n";
    std::cout << "  Command: " << metaCmd->getName() << "\n";
    std::cout << "========================================\n\n";

    std::cout << "Description:\n";
    std::cout << "  " << metaCmd->getDescription() << "\n\n";

    auto args = metaCmd->getArguments();
    if (!args.empty()) {
        std::cout << "Arguments:\n";

        // Separate required and optional arguments
        std::vector<MetaArgumentInfo> required;
        std::vector<MetaArgumentInfo> optional;

        for (const auto& arg : args) {
            if (arg.required) {
                required.push_back(arg);
            }
            else {
                optional.push_back(arg);
            }
        }

        // Show required arguments
        if (!required.empty()) {
            std::cout << "\n  Required:\n";
            for (const auto& arg : required) {
                std::cout << "    " << std::setw(20) << std::left << arg.name;
                std::cout << "\n";
            }
        }

        // Show optional arguments
        if (!optional.empty()) {
            std::cout << "\n  Optional:\n";
            for (const auto& arg : optional) {
                std::cout << "    " << std::setw(20) << std::left << arg.name;
                if (!arg.defaultValue.empty()) {
                    std::cout << " (default: " << arg.defaultValue << ")";
                }
                std::cout << "\n";
            }
        }
    }

    // Show usage examples
    std::cout << "\nUsage:\n";
    std::cout << "  " << metaCmd->getName();

    auto arguments = metaCmd->getArguments();
    for (const auto& arg : arguments) {
        if (arg.required && arg.name[0] != '-') {
            // Positional required argument
            std::cout << " <" << arg.name << ">";
        }
    }
    for (const auto& arg : arguments) {
        if (arg.required && arg.name[0] == '-') {
            // Required flag
            std::cout << " " << arg.name << " <value>";
        }
    }
    for (const auto& arg : arguments) {
        if (!arg.required && arg.name[0] == '-') {
            // Optional flag
            std::cout << " [" << arg.name << " <value>]";
        }
    }
    std::cout << "\n";

    std::cout << "\n========================================\n\n";
}