#ifndef SLIDE_H_
#define SLIDE_H_

#include "SlideObject.h"
#include "Rectangle.h"
#include "Circle.h"
#include "TextShape.h"
#include "Line.h"
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>

/*
struct TextArea
{
    std::string content;
    std::string fontFamily = "Arial";
    int fontSize = 12;
    std::string color = "black";
    std::string alignment = "left";
};
*/

class Slide {
private:
    int id;
    std::vector<SlideObject> objects;
    std::string text; // e.g., "title", "blank", "content" --------------------------------------
    //std::unordered_map<std::string, TextArea> textAreas;

public:
    explicit Slide(int id, std::string text = "blank")
        : id(id), text(std::move(text)) {}

    Slide(const Slide& other)
        : id(other.id), text(other.text), objects(other.objects) {}

    int getId() const;
    void setId(int newId);
    const std::string& getText() const;

    void addObject(SlideObject&& obj);

    void addRectangle(const std::string& name,
        size_t x, size_t y, size_t width, size_t height,
        const std::string& fillColor = "white",
        const std::string& borderColor = "black",
        size_t borderWidth = 1);

    void addCircle(const std::string& name,
        size_t centerX, size_t centerY, size_t radius,
        const std::string& fillColor = "white",
        const std::string& borderColor = "black",
        size_t borderWidth = 1);

    void addText(const std::string& name,
        size_t x, size_t y, size_t width, size_t height,
        const std::string& content,
        const std::string& font = "Arial",
        size_t fontSize = 12,
        const std::string& color = "black");

    void addLine(const std::string& name,
        size_t x1, size_t y1, size_t x2, size_t y2,
        const std::string& color = "black",
        size_t width = 1);

    SlideObject* getObject(const std::string& name);
    const SlideObject* getObject(const std::string& name) const;
    SlideObject* getObjectAt(size_t x, size_t y);
    bool hasObject(const std::string& name) const;
    const std::vector<SlideObject>& getObjects() const;
    bool moveObject(const std::string& name, size_t deltaX, size_t deltaY);
    bool resizeObject(const std::string& name, size_t newWidth, size_t newHeight);
    bool bringToFront(const std::string& name);
    bool sendToBack(const std::string& name);
    bool hasOverlaps() const;
    std::vector<std::pair<std::string, std::string>> getOverlaps() const;
    void display() const;
    size_t size() const;
};

#endif // SLIDE_H_
