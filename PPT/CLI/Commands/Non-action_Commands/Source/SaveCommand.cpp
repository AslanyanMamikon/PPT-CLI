#include "SaveCommand.h"


// SaveCommand implementation

SaveCommand::SaveCommand(const std::string& obj,
    const std::unordered_map<std::string, std::string>& f,
    const std::vector<std::string>& a)
    : object(obj), flags(f), args(a) {
}

void SaveCommand::execute(Presentation& presentation)
{
    validate();

    std::string filename = "presentation.json";

    if (!object.empty()) {
        filename = object;

        if (filename.find(".json") == std::string::npos) {
            filename += ".json";
        }
    }
    else if (auto it = flags.find("-file"); it != flags.end()) {
        filename = it->second;
    }

    if (JSONSerializer::saveToFile(presentation, filename)) {
        std::cout << "Presentation saved to: " << filename << "\n";
    }
    else {
        throw CommandValidationException("Failed to save presentation to file: " + filename);
    }
}

std::string SaveCommand::getName() const {
    return "save";
}

void SaveCommand::validate() const
{
    ArgumentValidator validator;
    validator.addInfo({ "-file", ArgumentType::String, false, {} });
    validator.validate(flags);
}

// LoadCommand implementation

LoadCommand::LoadCommand(const std::string& obj,
    const std::unordered_map<std::string, std::string>& f,
    const std::vector<std::string>& a)
    : object(obj), flags(f), args(a) {
}

void LoadCommand::execute(Presentation& presentation)
{
    validate();

    std::string filename = "presentation.json";

    if (!object.empty()) {
        filename = object;
        if (filename.find(".json") == std::string::npos) {
            filename += ".json";
        }
    }
    else if (auto it = flags.find("-file"); it != flags.end()) {
        filename = it->second;
    }
    else {
        throw CommandValidationException("Load command requires a filename");
    }

    if (JSONSerializer::loadFromFile(presentation, filename)) {
        std::cout << "Presentation loaded from: " << filename << "\n";
        std::cout << "Loaded " << presentation.size() << " slide(s)\n";
    }
    else {
        throw CommandValidationException("Failed to load presentation from file: " + filename);
    }
}

std::string LoadCommand::getName() const {
    return "load";
}

void LoadCommand::validate() const
{
    if (object.empty() && flags.find("-file") == flags.end()) {
        throw CommandValidationException("Load command requires a filename");
    }

    ArgumentValidator validator;
    validator.addInfo({ "-file", ArgumentType::String, false, {} });
    validator.validate(flags);
}