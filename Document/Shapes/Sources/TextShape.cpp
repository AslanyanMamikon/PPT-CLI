#include "TextShape.h"

void TextShape::draw() const
{
    std::cout << "Text '" << name << "' at ("
        << bounds.getTopLeft().x << "," << bounds.getTopLeft().y << ") "
        << bounds.getWidth() << "x" << bounds.getHeight()
        << "\n  Content: \"" << content << "\""
        << " [font: " << fontFamily << ", " << fontSize << "pt, "
        << fillColor << ", " << alignment << "]\n";
}

std::string TextShape::getType() const { return "Text"; }

std::unique_ptr<IShape> TextShape::clone() const
{
    return std::make_unique<TextShape>(*this);
}

// Text-specific methods
const std::string& TextShape::getContent() const { return content; }
void TextShape::setContent(const std::string& text) { content = text; }

const std::string& TextShape::getFont() const { return fontFamily; }
void TextShape::setFont(const std::string& font) { fontFamily = font; }

size_t TextShape::getFontSize() const { return fontSize; }
void TextShape::setFontSize(int size) { fontSize = size; }

const std::string& TextShape::getAlignment() const { return alignment; }
void TextShape::setAlignment(const std::string& align) { alignment = align; }