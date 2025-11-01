#ifndef TEXT_SHAPE_H_
#define TEXT_SHAPE_H_

#include "BaseShape.h"
#include <iostream>
#include <cmath>

class TextShape : public BaseShape
{
public:
    TextShape(const std::string& name, 
        size_t x, size_t y, size_t width, size_t height,
        const std::string& text = "",
        const std::string& font = "Arial", 
        int size = 12,
        const std::string& color = "black")
        : BaseShape(name, BoundingBox({ x, y }, { x + width, y + height }),
                    "transparent", "none", 0),
        content(text), fontFamily(font), fontSize(size), alignment("left") 
    {
        fillColor = color; // Text color
    }

    void draw() const override;
    std::string getType() const override;

    std::unique_ptr<IShape> clone() const override;

    // Text-specific methods
    const std::string& getContent() const;
    void setContent(const std::string& text);

    const std::string& getFont() const;
    void setFont(const std::string& font);

    size_t getFontSize() const;
    void setFontSize(int size);

    const std::string& getAlignment() const;
    void setAlignment(const std::string& align);

private:
	std::string content;
	std::string fontFamily;
	size_t fontSize;
	std::string alignment;
};


#endif // !TEXT_SHAPE_H_
