#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "BaseShape.h"
#include <iostream>
#include <cmath>

class Circle : public BaseShape
{
public:
	Circle(const std::string& name,
		size_t centerX, size_t centerY, size_t radius,
		/*const BoundingBox& bounds,*/
		const std::string& fillColor = "white",
		const std::string& borderColor = "black",
		size_t borderWidth = 1)
		: BaseShape(name, BoundingBox({ centerX - radius, centerY - radius },
									{ centerX + radius, centerY + radius }),
					fillColor, borderColor, borderWidth) {}

	void draw() const override;
	std::string getType() const override;

	std::unique_ptr<IShape> clone() const override;
};



#endif // !CIRCLE_H_
