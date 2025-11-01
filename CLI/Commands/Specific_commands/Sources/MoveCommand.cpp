#include "MoveCommand.h"

void MoveSlideCommand::execute(Presentation& presentation)
{
	int from = std::stoi(flags.at("-from"));
	int to = std::stoi(flags.at("-to"));

	presentation.moveSlide(from, to);
	std::cout << "Moved slide from position " << from << " to position " << to << "\n";
}

std::string MoveSlideCommand::getName() const { return "move"; }

void MoveSlideCommand::validate() const
{
	if (object != "slide") {
		throw CommandValidationException("Move command supports only: slide");
	}

	ArgumentValidator validator;
	validator.addInfo({ "-from", ArgumentType::Integer, true, {} });
	validator.addInfo({ "-to", ArgumentType::Integer, true, {} });
	validator.validate(flags);
}