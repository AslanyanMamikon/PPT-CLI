#include "Circle.h"

void Circle::draw() const
{
	size_t x1 = bounds.getTopLeft().x;
	size_t y1 = bounds.getTopLeft().y;
	size_t x2 = bounds.getBottomRight().x;
	size_t y2 = bounds.getBottomRight().y;

	size_t centerX = (x1 + x2) / 2;
	size_t centerY = (y1 + y2) / 2;
	size_t radius = bounds.getWidth() / 2;

	std::cout << "Circle '" << name << "' at center ("
		<< centerX << "," << centerY << ") "
		<< "radius: " << radius
		<< " [fill: " << fillColor << ", border: " << borderColor << "]\n";

}

std::string Circle::getType() const { return "Circle"; }

std::unique_ptr<IShape> Circle::clone() const
{
	return std::make_unique<Circle>(*this);
}