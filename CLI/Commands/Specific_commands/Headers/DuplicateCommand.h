#ifndef DUPLICATE_COMMAND_H_
#define DUPLICATE_COMMAND_H_

#include "ICommand.h"
#include "Argument.h"
#include "Presentation.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <sstream>

class DuplicateSlideCommand : public ICommand
{
private:
	std::string object;
	std::unordered_map<std::string, std::string> flags;
	std::vector<std::string> args;

public:
	DuplicateSlideCommand(const std::string& obj,
		const std::unordered_map<std::string, std::string>& f,
		const std::vector<std::string>& a)
		: object(obj), flags(f), args(a) {}
	
	void execute(Presentation& presentation) override;
	std::string getName() const override;

protected:
	void validate() const override;
};

#endif // !DUPLICATE_COMMAND_H_
