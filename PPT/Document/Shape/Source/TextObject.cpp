#include "TextObject.h"
#include <iostream>

TextObject::TextObject(const std::string& name,
    size_t x, size_t y, size_t width, size_t height,
    const std::string& content,
    const std::string& font,
    size_t fontSize,
    const std::string& color)
    : BaseSlideObject(name, Geometry(x, y, x + width, y + height)),
    content(content),
    font(font),
    fontSize(fontSize),
    color(color),
    alignment("left") {
}

std::string TextObject::getType() const {
    return "Text";
}

void TextObject::draw() const {
    std::cout << "Text '" << name << "' at ("
        << geometry.getTopLeft().x << "," << geometry.getTopLeft().y << ") "
        << geometry.getWidth() << "x" << geometry.getHeight()
        << "\n  Content: \"" << content << "\""
        << " [font: " << font << ", " << fontSize << "pt, "
        << color << ", " << alignment << "]\n";
}

std::unique_ptr<SlideObject> TextObject::clone() const {
    return std::make_unique<TextObject>(*this);
}

const std::string& TextObject::getContent() const {
    return content;
}

void TextObject::setContent(const std::string& text) {
    content = text;
}

const std::string& TextObject::getFont() const {
    return font;
}

void TextObject::setFont(const std::string& f) {
    font = f;
}

size_t TextObject::getFontSize() const {
    return fontSize;
}

void TextObject::setFontSize(size_t size) {
    fontSize = size;
}

const std::string& TextObject::getColor() const {
    return color;
}

void TextObject::setColor(const std::string& c) {
    color = c;
}

const std::string& TextObject::getAlignment() const {
    return alignment;
}

void TextObject::setAlignment(const std::string& align) {
    alignment = align;
}