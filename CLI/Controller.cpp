#include "Controller.h"

bool Controller::processCommand(std::istream& stream) {
	lastError.clear();

	try {
		Parser parser(stream);
		std::unique_ptr<ICommand> command = parser.parse(&shouldExit);
		
		if (!command) {
			lastError = parser.getError();
			return false;
		}
		command->execute(presentation);

		return true;
	}
	catch (const CommandValidationException& e) {
		lastError = std::string("Validation error: ") + e.what();
		return false;
	}
	catch (const std::exception& e) {
		lastError = std::string("Error: ") + e.what();
		return false;
	}
}

bool Controller::processCommand(const std::string& input) {
	std::istringstream stream(input);
	return processCommand(stream);
}