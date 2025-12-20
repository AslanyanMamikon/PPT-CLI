#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "BaseSlideObject.h"

class Circle : public BaseSlideObject {
private:
    std::string fillColor;
    std::string borderColor;
    size_t borderWidth;
    size_t radius;

public:
    Circle(const std::string& name,
        size_t centerX, size_t centerY, size_t radius,
        const std::string& fillColor = "white",
        const std::string& borderColor = "black",
        size_t borderWidth = 1);

    std::string getType() const override;
    void draw() const override;
    std::unique_ptr<SlideObject> clone() const override;

    void setGeometry(const Geometry& geom) override;
    size_t getRadius() const;
    void setRadius(size_t r);
    std::string getFillColor() const;
    void setFillColor(const std::string& color);
    std::string getBorderColor() const;
    void setBorderColor(const std::string& color);
    size_t getBorderWidth() const;
    void setBorderWidth(size_t width);
};

#endif // CIRCLE_H_