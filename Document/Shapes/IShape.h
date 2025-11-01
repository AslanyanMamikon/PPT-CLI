#ifndef ISHAPE_H_
#define ISHAPE_H_

#include <string>
#include <memory>

struct Point
{
	size_t x;
	size_t y;

	Point(size_t x = 0, size_t y = 0)
		: x(x), y(y) {}
};

class BoundingBox
{
public:

	//BoundingBox() : Top_left({ 0.f, 0.f }), Bottom_right({ 0.f, 0.f }) {}
	BoundingBox() : Top_left({0, 0}), Bottom_right({0, 0}) {}
	BoundingBox(Point p1, Point p2) : Top_left(p1), Bottom_right(p2) {}
	BoundingBox(size_t x1, size_t y1, size_t x2, size_t y2)
		: Top_left(x1, y1), Bottom_right(x2, y2) {}

	size_t getWidth() const { return Bottom_right.x - Top_left.x; }
	size_t getHeight() const { return Bottom_right.y - Top_left.y; }
	Point getTopLeft() const { return Top_left; }
	Point getBottomRight() const { return Bottom_right; }

	size_t getCenterX() const { return (Top_left.x + Bottom_right.x) / 2; }
	size_t getCenterY() const { return (Top_left.y + Bottom_right.y) / 2; }

	void setTopLeft(size_t x, size_t y) 
	{
		Top_left.x = x;
		Top_left.y = y;
	}

	void setBottomRight(size_t x, size_t y)
	{
		Bottom_right.x = x;
		Bottom_right.y = y;
	}


	bool contains(size_t x, size_t y) const
	{
		return x >= Top_left.x && x <= Bottom_right.x 
				&& y >= Top_left.y && y <= Bottom_right.y;
	}

	bool intersects(const BoundingBox& other) const
	{
		return !(Bottom_right.x < other.Top_left.x ||
			other.Bottom_right.x < Top_left.x ||
			Bottom_right.y < other.Top_left.y ||
			other.Bottom_right.y < Top_left.y);
	}

	void move(size_t deltaX, size_t deltaY)
	{
		Top_left.x += deltaX;
		Top_left.y += deltaY;
		Bottom_right.x += deltaX;
		Bottom_right.y += deltaY;
	}

	void resize(size_t newWidth, size_t newHeight)
	{
		Bottom_right.x = Top_left.x + newWidth;
		Bottom_right.y = Top_left.y + newHeight;
	}

private:
	Point Top_left;
	Point Bottom_right;
};

class IShape
{
public:
	virtual ~IShape() = default;

	virtual void draw() const = 0; //-------------------------------

	virtual BoundingBox getBounds() const = 0;
	virtual void move(size_t deltaX, size_t deltaY) = 0;
	virtual void resize(size_t newWidth, size_t newHeight) = 0;

	virtual std::string getType() const = 0;

	virtual std::string getName() const = 0;
	virtual void setName(const std::string& name) = 0;
	virtual std::string getFillColor() const = 0;
	virtual void setFillColor(const std::string& color) = 0;
	virtual std::string getBorderColor() const = 0;
	virtual void setBorderColor(const std::string& color) = 0;
	virtual size_t getBorderWidth() const = 0;
	virtual void setBorderWidth(size_t width) = 0;

	virtual std::unique_ptr<IShape> clone() const = 0;
};

#endif // !ISHAPE_H_
