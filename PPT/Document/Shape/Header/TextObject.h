#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "BaseSlideObject.h"

class TextObject : public BaseSlideObject {
private:
    std::string content;
    std::string font;
    size_t fontSize;
    std::string color;
    std::string alignment;

public:
    TextObject(const std::string& name,
        size_t x, size_t y, size_t width, size_t height,
        const std::string& content = "",
        const std::string& font = "Arial",
        size_t fontSize = 12,
        const std::string& color = "black");

    std::string getType() const override;
    void draw() const override;
    std::unique_ptr<SlideObject> clone() const override;

    // Text-specific methods
    const std::string& getContent() const;
    void setContent(const std::string& text);
    const std::string& getFont() const;
    void setFont(const std::string& f);
    size_t getFontSize() const;
    void setFontSize(size_t size);
    const std::string& getColor() const;
    void setColor(const std::string& c);
    const std::string& getAlignment() const;
    void setAlignment(const std::string& align);
};

#endif // TEXT_OBJECT_H_