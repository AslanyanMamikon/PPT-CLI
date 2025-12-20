#include "ExitCommand.h"

void ExitCommand::execute(Presentation& presentation)
{
	validate();

	std::cout << "Exiting presentation CLI...\n";
	shouldExit = true;
}

std::string ExitCommand::getName() const { return "exit"; }

void ExitCommand::validate() const
{
	if (!object.empty())
		throw CommandValidationException("Exit command takes no object");

	if (!flags.empty())
		throw CommandValidationException("Exit command takes no flags");

	if (!args.empty())
		throw CommandValidationException("Exit command takes no arguments");
}