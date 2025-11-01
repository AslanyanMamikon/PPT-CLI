#include "DuplicateCommand.h"

void DuplicateSlideCommand::execute(Presentation& presentation)
{
	int pos = std::stoi(flags.at("-pos"));
	presentation.duplicateSlide(pos);
	std::cout << "Duplicated slide at position " << pos << "\n";
}

std::string DuplicateSlideCommand::getName() const { return "Duplicate"; }

void DuplicateSlideCommand::validate() const
{
	if (object != "slide")
		throw CommandValidationException("Duplicate command supports only: slide");

	ArgumentValidator validator;
	validator.addInfo({ "-pos", ArgumentType::Integer, true, {} });
	validator.validate(flags);
}