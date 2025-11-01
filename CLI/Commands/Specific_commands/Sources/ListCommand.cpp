#include "ListCommand.h"

void ListSlidesCommand::execute(Presentation& presentation)
{
    validate();

    if (presentation.size() == 0)
        throw CommandValidationException("Presentation is empty. No slides to list.");

    presentation.listSlides();
}

std::string ListSlidesCommand::getName() const { return "list"; }

void ListSlidesCommand::validate() const
{
    if (!object.empty() && object != "slides" && object != "slide") {
        throw CommandValidationException("List command only supports 'slides' or no object");
    }
}