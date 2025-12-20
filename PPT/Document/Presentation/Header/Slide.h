#ifndef SLIDE_H_
#define SLIDE_H_

#include "SlideObject.h"
#include "Geometry.h"
#include "ICanvas.h"
#include "IPainter.h"
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <iostream>

class Slide {
private:
    int id;
    std::string layoutType; // "title", "blank", "content"
    std::vector<std::unique_ptr<SlideObject>> objects;

public:
    explicit Slide(int id, std::string layout = "blank");

    // Copy constructor for duplication
    Slide(const Slide& other);

    // Disable assignment for safety
    Slide& operator=(const Slide&) = delete;


    int getId() const;
    void setId(int newId);
    const std::string& getText() const;

    void addObject(std::unique_ptr<SlideObject> obj);


    SlideObject* getObject(const std::string& name);
    const SlideObject* getObject(const std::string& name) const;
    SlideObject* getObjectAt(size_t x, size_t y);
    bool hasObject(const std::string& name) const;
    const std::vector<std::unique_ptr<SlideObject>>& getObjects() const;


    bool moveObject(const std::string& name, size_t deltaX, size_t deltaY);
    bool resizeObject(const std::string& name, size_t newWidth, size_t newHeight);
    bool bringToFront(const std::string& name);
    bool sendToBack(const std::string& name);


    bool hasOverlaps() const;
    std::vector<std::pair<std::string, std::string>> getOverlaps() const;


    void display() const;
    size_t size() const;

    void renderToCanvas(ICanvas& canvas, const IPainter& painter) const;

private:

    std::string getBackgroundColor() const;
};

#endif // SLIDE_H_