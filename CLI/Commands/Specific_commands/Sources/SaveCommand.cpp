#include "SaveCommand.h"

void SaveCommand::execute(Presentation& presentation)
{
    validate();

    std::string filename = "presentation.json";

    // Check if filename is provided as object (e.g., "save PyPresentation")
    if (!object.empty()) {
        filename = object;
        // Add .json extension if not present
        if (filename.find(".json") == std::string::npos) {
            filename += ".json";
        }
    }
    // Otherwise check for -file flag
    else if (auto it = flags.find("-file"); it != flags.end()) {
        filename = it->second;
    }

    if (JSONSerializer::saveToFile(presentation, filename)) {
        std::cout << "Presentation saved to: " << filename << "\n";
    }
    else
        throw CommandValidationException("Failed to save presentation to file: " + filename);
}

std::string SaveCommand::getName() const { return "save"; }

void SaveCommand::validate() const
{
    // Object is optional - can be used as filename
    ArgumentValidator validator;
    validator.addInfo({ "-file", ArgumentType::String, false, {} });
    validator.validate(flags);
}

// LoadCommand implementation

void LoadCommand::execute(Presentation& presentation)
{
    validate();

    std::string filename = "presentation.json";

    // Check if filename is provided as object (e.g., "load PyPresentation")
    if (!object.empty()) {
        filename = object;
        // Add .json extension if not present
        if (filename.find(".json") == std::string::npos) {
            filename += ".json";
        }
    }
    // Otherwise check for -file flag
    else if (auto it = flags.find("-file"); it != flags.end()) {
        filename = it->second;
    }
    // If neither provided, require filename
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

std::string LoadCommand::getName() const { return "load"; }

void LoadCommand::validate() const
{
    // Object is optional - can be used as filename
    // But at least object or -file flag must be provided
    if (object.empty() && flags.find("-file") == flags.end()) {
        throw CommandValidationException("Load command requires a filename");
    }

    ArgumentValidator validator;
    validator.addInfo({ "-file", ArgumentType::String, false, {} });
    validator.validate(flags);
}