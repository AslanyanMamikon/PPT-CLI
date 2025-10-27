#ifndef SLIDE_OBJECT_H_
#define SLIDE_OBJECT_H_

#include <string>

enum class ObjectType {
    TEXT,
    IMAGE,
    SHAPE
};

struct Position {
    int x = 0;
    int y = 0;
};

struct Size {
    int width = 0;
    int height = 0;
};

class SlideObject {
public:
    SlideObject(ObjectType type, std::string name)
        : type(type), name(std::move(name)) {
    }

    ObjectType type;
    std::string name; 
    std::string color;
    int fontSize = 12;
    Position pos;
    Size size;

    void draw() const;  // For later graphical extension
};

#endif // SLIDE_OBJECT_H_
