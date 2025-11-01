#include "BaseShape.h"

void BaseShape::move(size_t deltaX, size_t deltaY)
{
	/*
	size_t x1 = bounds.getTopLeft().x + deltaX;
	size_t y1 = bounds.getTopLeft().y + deltaY;
	size_t x2 = bounds.getBottomRight().x + deltaX;
	size_t y2 = bounds.getBottomRight().y + deltaY;

	bounds.setTopLeft(x1, y1);
	bounds.setBottomRight(x2, y2);
	*/
	bounds.move(deltaX, deltaY);
}

void BaseShape::resize(size_t newWidth, size_t newHeight)
{
	/*
	size_t x1 = bounds.getTopLeft().x;
	size_t y1 = bounds.getTopLeft().y;
	size_t x2 = x1 + newWidth;
	size_t y2 = y1 + newHeight;

	bounds.setBottomRight(x2, y2);
	*/
	bounds.resize(newWidth, newHeight);
}

BoundingBox BaseShape::getBounds() const { return bounds; }

std::string BaseShape::getName() const { return name; }
void BaseShape::setName(const std::string& n) { name = n; }

std::string BaseShape::getFillColor() const { return fillColor; }
void BaseShape::setFillColor(const std::string& color) { fillColor = color; }

std::string BaseShape::getBorderColor() const { return borderColor; }
void BaseShape::setBorderColor(const std::string& color) { borderColor = color; }

size_t BaseShape::getBorderWidth() const { return borderWidth; }
void BaseShape::setBorderWidth(size_t width) { borderWidth = width; }