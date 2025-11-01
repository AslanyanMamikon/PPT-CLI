#ifndef ADD_COMMAND_H_
#define ADD_COMMAND_H_

#include "ICommand.h"
#include "Argument.h"
#include "Presentation.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <sstream>

class AddSlideCommand : public ICommand {
private:
    std::string object;
    std::unordered_map<std::string, std::string> flags;
    std::vector<std::string> args;

public:
    AddSlideCommand(const std::string& obj,
        const std::unordered_map<std::string, std::string>& f,
        const std::vector<std::string>& a)
        : object(obj), flags(f), args(a)
    {
        //validate();
    }

    void execute(Presentation& presentation) override {
        validate();

        std::string text = "blank";
        if (auto it = flags.find("-text"); it != flags.end())
            text = it->second;

        auto posIt = flags.find("-pos");

        if (posIt != flags.end() && posIt->second.find(',') != std::string::npos)
        {
            std::vector<int> positions = parsePosition(posIt->second);
            for (int pos : positions)
            {
                presentation.addSlideAtPosition(pos, text);
                std::cout << "Added slide at position " << pos << " with text: " << text << "\n";
            }
        }
        else if (posIt != flags.end())
        {
            int pos = std::stoi(posIt->second);
            presentation.addSlideAtPosition(pos, text);
            std::cout << "Added slide at position " << pos << " with text: " << text << "\n";
        }
        else
        {
            Slide& slide = presentation.addSlide(text);
            std::cout << "Added new slide with ID: " << slide.getId() << " (text: " << text << ")\n";
        }
    }

    std::string getName() const override { return "add"; }

protected:

    void validate() const {
        if (object != "slide" && object != "text" && object != "image") {
            throw CommandValidationException("Add command supports only: slide, text, image");
        }

        ArgumentValidator validator;
        validator.addInfo({ "-text", ArgumentType::Enum, false, {"title", "blank", "content"} });
        validator.addInfo({ "-pos", ArgumentType::String, false, {} });
        validator.addInfo({ "-width", ArgumentType::Integer, false, {} });
        validator.addInfo({ "-height", ArgumentType::Integer, false, {} });

        validator.validate(flags);
    }
private:
    std::vector<int> parsePosition(const std::string& posStr) const
    {
        std::vector<int> positions;
        std::stringstream ss(posStr);
        std::string token;
        while (std::getline(ss, token, ','))
            positions.push_back(std::stoi(token));
        return positions;
    }
};

#endif // !ADD_COMMAND_H_
