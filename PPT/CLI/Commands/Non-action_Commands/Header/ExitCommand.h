#ifndef EXIT_COMMAND_H_
#define EXIT_COMMAND_H_

#include "ICommand.h"
#include "Presentation.h"
#include <vector>
#include <unordered_map>
#include <iostream>

class ExitCommand : public ICommand
{
private:
	std::string object;
	std::unordered_map<std::string, std::string> flags;
	std::vector<std::string> args;
	bool& shouldExit;

public:
	ExitCommand(const std::string& obj,
		const std::unordered_map<std::string, std::string>& f,
		const std::vector<std::string>& a,
		bool& exitFlag)
		: object(obj), flags(f), args(a), shouldExit(exitFlag) {}

	void execute(Presentation& presentation) override;
	std::string getName() const override;

protected:
	void validate() const override;
};


#endif // EXIT_COMMAND_H_