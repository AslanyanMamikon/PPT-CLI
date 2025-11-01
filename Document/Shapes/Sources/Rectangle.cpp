#include "Rectangle.h"

void Rectangle::draw() const
{
	std::cout << "Rectangle '" << name << "' at ("
		<< bounds.getTopLeft().x << ", " << bounds.getTopLeft().y << ") "
		<< bounds.getWidth() << "x" << bounds.getHeight()
		<< " [fill: " << fillColor << ", border: " << borderColor << "]\n";
}

std::string Rectangle::getType() const { return "Rectangle"; }

std::unique_ptr<IShape> Rectangle::clone() const
{
	return std::make_unique<Rectangle>(*this);
}