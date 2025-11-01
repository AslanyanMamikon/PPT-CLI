#ifndef ADD_SHAPE_COMMAND_H_
#define ADD_SHAPE_COMMAND_H_

#include "ICommand.h"
#include "Argument.h"
#include "Presentation.h"
#include <vector>
#include <unordered_map>
#include <iostream>

class AddShapeCommand : public ICommand
{
private:
	std::string object;
	std::unordered_map<std::string, std::string> flags;
	std::vector<std::string> args;

public:
	AddShapeCommand(const std::string& obj,
		const std::unordered_map<std::string, std::string>& f,
		const std::vector<std::string>& a)
		: object(obj), flags(f), args(a) {}

	void execute(Presentation& presentation) override;
	std::string getName() const override;

protected:
	void validate() const override;

private:

	void addRectangle(Slide& slide);

	void addCircle(Slide& slide);
	void addText(Slide& slide);
	void addLine(Slide& slide);
	std::string getFlag(const std::string& flagName, const std::string& defaultValue) const;
};

#endif // !ADD_SHAPE_COMMAND_H_
