#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "BaseShape.h"
#include <iostream>
#include <cmath>

class Rectangle : public BaseShape
{
public:
	Rectangle(const std::string& name,
		const BoundingBox& bounds,
		const std::string& fillColor = "white",
		const std::string& borderColor = "black",
		size_t borderWidth = 1)
		: BaseShape(name, bounds, fillColor, borderColor, borderWidth) {}

	Rectangle(const std::string& name,
		size_t x, size_t y, size_t width, size_t height,
		const std::string& fillColor = "white",
		const std::string& borderColor = "black",
		size_t borderWidth = 1)
		: BaseShape(name, BoundingBox(x, y, x + width, y + height),
			fillColor, borderColor, borderWidth) {}

	void draw() const override;
	std::string getType() const override;

	std::unique_ptr<IShape> clone() const override;
};

#endif // !RECTANGLE_H_
