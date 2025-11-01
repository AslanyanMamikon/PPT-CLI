#ifndef MOVE_COMMAND_H_
#define MOVE_COMMAND_H_

#include "ICommand.h"
#include "Argument.h"
#include "Presentation.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <sstream>


class MoveSlideCommand : public ICommand
{
private:
	std::string object;
	std::unordered_map<std::string, std::string> flags;
	std::vector<std::string> args;

public:
	MoveSlideCommand(const std::string& obj,
		const std::unordered_map<std::string, std::string>& f,
		const std::vector<std::string>& a)
		: object(obj), flags(f), args(a) { }
	
	void execute(Presentation& presentation) override;
	std::string getName() const override;

protected:
	void validate() const override;
};

#endif // !MOVE_COMMAND_H_
