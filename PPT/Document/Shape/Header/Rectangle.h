#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "BaseSlideObject.h"

class Rectangle : public BaseSlideObject {
private:
    std::string fillColor;
    std::string borderColor;
    size_t borderWidth;

public:
    Rectangle(const std::string& name,
        size_t x, size_t y, size_t width, size_t height,
        const std::string& fillColor = "white",
        const std::string& borderColor = "black",
        size_t borderWidth = 1);

    Rectangle(const std::string& name,
        const Geometry& geom,
        const std::string& fillColor = "white",
        const std::string& borderColor = "black",
        size_t borderWidth = 1);

    std::string getType() const override;
    void draw() const override;
    std::unique_ptr<SlideObject> clone() const override;

    // Rectangle-specific methods
    std::string getFillColor() const;
    void setFillColor(const std::string& color);
    std::string getBorderColor() const;
    void setBorderColor(const std::string& color);
    size_t getBorderWidth() const;
    void setBorderWidth(size_t width);
};

#endif // RECTANGLE_H_