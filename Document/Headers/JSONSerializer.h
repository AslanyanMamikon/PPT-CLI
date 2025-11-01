#ifndef JSON_SERIALIZER_H_
#define JSON_SERIALIZER_H_

#include "Presentation.h"
#include "Slide.h"
#include "SlideObject.h"
#include "IShape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "TextShape.h"
#include "Line.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

using json = nlohmann::json;

class JSONSerializer {
public:
    static bool saveToFile(const Presentation& presentation, const std::string& filename);
    static bool loadFromFile(Presentation& presentation, const std::string& filename);

private:
    static json serializePresentation(const Presentation& presentation);
    static json serializeSlide(const Slide& slide);
    static json serializeSlideObject(const SlideObject& obj);
    static json serializeShape(const IShape* shape);
    static json serializeBoundingBox(const BoundingBox& bounds);

    static void deserializePresentation(Presentation& presentation, const json& j);
    static std::unique_ptr<Slide> deserializeSlide(const json& j);
    static SlideObject deserializeSlideObject(const json& j);
    static std::unique_ptr<IShape> deserializeShape(const json& j);
    static BoundingBox deserializeBoundingBox(const json& j);
};

#endif // JSON_SERIALIZER_H_