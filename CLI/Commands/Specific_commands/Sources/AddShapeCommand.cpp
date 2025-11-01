#include "AddShapeCommand.h"



void AddShapeCommand::execute(Presentation& presentation)
{
	validate();

	int slidePos = 1;
	if (auto it = flags.find("-slide"); it != flags.end())
		slidePos = std::stoi(it->second);
	else
		slidePos = static_cast<int>(presentation.size());

	Slide* slide = presentation.getSlideAtPosition(slidePos);
	if (!slide)
		throw CommandValidationException("Slide at position " +
			std::to_string(slidePos) + " doesn't exist");

	std::string name = flags.at("-name");

	if (object == "rectangle") {
		addRectangle(*slide);
	}
	else if (object == "circle") {
		addCircle(*slide);
	}
	else if (object == "text") {
		addText(*slide);
	}
	else if (object == "line") {
		addLine(*slide);
	}
}

std::string AddShapeCommand::getName() const { return "add shape"; }


void AddShapeCommand::validate() const
{
	if (object != "rectangle" && object != "circle" &&
		object != "text" && object != "line")
		throw CommandValidationException(
			"Add shape supports: rectangle, circle, text, line");

	ArgumentValidator validator;
	validator.addInfo({ "-name", ArgumentType::String, true, {} });
	validator.addInfo({ "-slide", ArgumentType::Integer, false, {} });
	validator.addInfo({ "-x", ArgumentType::Integer, true, {} });
	validator.addInfo({ "-y", ArgumentType::Integer, true, {} });

	if (object == "rectangle" || object == "text") {
		validator.addInfo({ "-width", ArgumentType::Integer, true, {} });
		validator.addInfo({ "-height", ArgumentType::Integer, true, {} });
	}
	else if (object == "circle") {
		validator.addInfo({ "-radius", ArgumentType::Integer, true, {} });
	}
	else if (object == "line") {
		validator.addInfo({ "-x2", ArgumentType::Integer, true, {} });
		validator.addInfo({ "-y2", ArgumentType::Integer, true, {} });
	}

	validator.addInfo({ "-fill", ArgumentType::String, false, {} });
	validator.addInfo({ "-border", ArgumentType::String, false, {} });
	validator.addInfo({ "-border-width", ArgumentType::Integer, false, {} });

	validator.validate(flags);
}

void AddShapeCommand::addRectangle(Slide& slide)
{
	std::string name = flags.at("-name");
	size_t x = std::stoi(flags.at("-x"));
	size_t y = std::stoi(flags.at("-y"));
	size_t width = std::stoi(flags.at("-width"));
	size_t height = std::stoi(flags.at("-height"));

	std::string fill = getFlag("-fill", "white");
	std::string border = getFlag("-border", "black");
	size_t borderWidth = std::stoi(getFlag("-border-width", "1"));

	slide.addRectangle(name, x, y, width, height, fill, border, borderWidth);
	std::cout << "Added rectangle '" << name << "' to slide\n";
}

void AddShapeCommand::addCircle(Slide& slide)
{
	std::string name = flags.at("-name");
	size_t x = std::stoi(flags.at("-x"));
	size_t y = std::stoi(flags.at("-y"));
	size_t radius = std::stoi(flags.at("-radius"));

	std::string fill = getFlag("-fill", "white");
	std::string border = getFlag("-border", "black");
	size_t borderWidth = std::stoi(getFlag("-border-width", "1"));

	slide.addCircle(name, x, y, radius, fill, border, borderWidth);
	std::cout << "Added circle '" << name << "' to slide\n";
}

void AddShapeCommand::addText(Slide& slide)
{
	std::string name = flags.at("-name");
	size_t x = std::stoi(flags.at("-x"));
	size_t y = std::stoi(flags.at("-y"));
	size_t width = std::stoi(flags.at("-width"));
	size_t height = std::stoi(flags.at("-height"));

	std::string content = getFlag("-content", "");
	std::string font = getFlag("-font", "Arial");
	size_t fontSize = std::stoi(getFlag("-font-size", "12"));
	std::string color = getFlag("-color", "black");

	slide.addText(name, x, y, width, height, content, font, fontSize, color);
	std::cout << "Added text '" << name << "' to slide\n";
}

void AddShapeCommand::addLine(Slide& slide)
{
	std::string name = flags.at("-name");
	size_t x1 = std::stoi(flags.at("-x"));
	size_t y1 = std::stoi(flags.at("-y"));
	size_t x2 = std::stoi(flags.at("-x2"));
	size_t y2 = std::stoi(flags.at("-y2"));

	std::string color = getFlag("-color", "black");
	size_t width = std::stoi(getFlag("-width", "1"));

	slide.addLine(name, x1, y1, x2, y2, color, width);
	std::cout << "Added line '" << name << "' to slide\n";
}

std::string AddShapeCommand::getFlag(const std::string& flagName, const std::string& defaultValue) const
{
	auto it = flags.find(flagName);
	return (it != flags.end()) ? it->second : defaultValue;
}