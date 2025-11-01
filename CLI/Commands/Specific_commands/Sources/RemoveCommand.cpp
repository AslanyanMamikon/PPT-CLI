#include "RemoveCommand.h"

void RemoveSlideCommand::execute(Presentation& presentation)
{
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

std::string RemoveSlideCommand::getName() const { return "remove"; }

void RemoveSlideCommand::validate() const
{
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