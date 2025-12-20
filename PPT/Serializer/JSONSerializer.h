#ifndef JSON_SERIALIZER_H_
#define JSON_SERIALIZER_H_

#include "Presentation.h"
#include "Slide.h"
#include "SlideObject.h"
#include "Rectangle.h"
#include "Circle.h"
#include "TextObject.h"
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
    static json serializeSlideObject(const SlideObject* obj);
    static json serializeGeometry(const Geometry& geom);

    static void deserializePresentation(Presentation& presentation, const json& j);
    static std::unique_ptr<Slide> deserializeSlide(const json& j);
    static std::unique_ptr<SlideObject> deserializeSlideObject(const json& j);
    static Geometry deserializeGeometry(const json& j);
};

#endif // JSON_SERIALIZER_H_