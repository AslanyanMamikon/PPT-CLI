#ifndef REMOVE_COMMAND_H_
#define REMOVE_COMMAND_H_

#include "ICommand.h"
#include "Argument.h"
#include "Presentation.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <sstream>

class RemoveSlideCommand : public ICommand {
private:
    std::string object;
    std::unordered_map<std::string, std::string> flags;
    std::vector<std::string> args;

public:
    RemoveSlideCommand(const std::string& obj,
        const std::unordered_map<std::string, std::string>& f,
        const std::vector<std::string>& a)
        : object(obj), flags(f), args(a)
    {
        //validate();
    }

    void execute(Presentation& presentation) override {
        validate();

        if (presentation.size() == 0)
            throw CommandValidationException("Can't remove slide: presentation is empty");

        auto posIt = flags.find("-pos");

        if (posIt != flags.end())
        {
            int pos = std::stoi(posIt->second);
            presentation.removeSlideAtPosition(pos);
            std::cout << "Remove slide at position " << pos << "\n";
        }
        else
        {
            presentation.removeLastSlide();
            std::cout << "Removed last slide\n";
        }

        /*
        int slideId = std::stoi(args[0]);
        if (!presentation.hasSlide(slideId))
            throw CommandValidationException("Slide with ID " + std::to_string(slideId) + " doesn't exist");

        if (args.empty())
            throw CommandValidationException("Remove slide requires slide ID");

        presentation.removeSlide(slideId);
        std::cout << "Removed slide with ID: " << slideId << "\n";
        */
    }

    std::string getName() const override { return "remove"; }

protected:
    void validate() const {
        if (object != "slide")
            throw CommandValidationException("Remove command supports only: slide");
        /*
        if (args.empty())
            throw CommandValidationException("Slide ID required");
        
        
        try
        {
            std::stoi(args[0]);
        }
        catch (const std::exception&)
        {
            throw CommandValidationException("Invalid Slide ID: must be an integer");
        }
        */
    }
};


#endif // !REMOVE_COMMAND_H_
