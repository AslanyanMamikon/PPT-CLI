#ifndef BASE_SHAPE_H_
#define BASE_SHAPE_H_

#include "IShape.h"
#include <iostream>
#include <cmath>

class BaseShape : public IShape
{
protected:
	std::string name;
	BoundingBox bounds;
	std::string fillColor;
	std::string borderColor;
	size_t borderWidth;

public:
	BaseShape(const std::string& name,	
			const BoundingBox& bounds,
			const std::string& fillColor = "white", 
			const std::string& borderColor = "black",
			size_t borderWidth = 1)
		: name(name), bounds(bounds), fillColor(fillColor),
		borderColor(borderColor), borderWidth(borderWidth) {}

	virtual ~BaseShape() = default;	

	void move(size_t deltaX, size_t deltaY) override;
	void resize(size_t newWidth, size_t newHeight) override;

	BoundingBox getBounds() const override;

	std::string getName() const override;
	void setName(const std::string& n) override;

	std::string getFillColor() const override;
	void setFillColor(const std::string& color) override;

	std::string getBorderColor() const override;
	void setBorderColor(const std::string& color) override;

	size_t getBorderWidth() const override;
	void setBorderWidth(size_t width) override;
};

#endif // !BASE_SHAPE_H_
