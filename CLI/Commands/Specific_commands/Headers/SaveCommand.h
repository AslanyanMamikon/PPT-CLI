#ifndef SAVE_COMMAND_H_
#define SAVE_COMMAND_H_

#include "ICommand.h"
#include "Argument.h"
#include "Presentation.h"
#include "Slide.h"
#include "SlideObject.h"
#include "IShape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "TextShape.h"
#include "Line.h"
#include "JSONSerializer.h"
#include <nlohmann/json.hpp>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>

using json = nlohmann::json;

class SaveCommand : public ICommand
{
private:
    std::string object;
    std::unordered_map<std::string, std::string> flags;
    std::vector<std::string> args;

    // Serialization helpers
    static json serializePresentation(const Presentation& presentation);
    static json serializeSlide(const Slide& slide);
    static json serializeSlideObject(const SlideObject& obj);
    static json serializeShape(const IShape* shape);
    static json serializeBoundingBox(const BoundingBox& bounds);

    // Helper to generate unique filename
    static std::string generateUniqueFilename(const std::string& baseName);

public:
    SaveCommand(const std::string& obj,
        const std::unordered_map<std::string, std::string>& f,
        const std::vector<std::string>& a)
        : object(obj), flags(f), args(a) {
    }

    void execute(Presentation& presentation) override;
    std::string getName() const override;

protected:
    void validate() const override;
};


class LoadCommand : public ICommand
{
private:
    std::string object;
    std::unordered_map<std::string, std::string> flags;
    std::vector<std::string> args;

    // Deserialization helpers
    static void deserializePresentation(Presentation& presentation, const json& j);
    static std::unique_ptr<Slide> deserializeSlide(const json& j);
    static SlideObject deserializeSlideObject(const json& j);
    static std::unique_ptr<IShape> deserializeShape(const json& j);
    static BoundingBox deserializeBoundingBox(const json& j);

public:
    LoadCommand(const std::string& obj,
        const std::unordered_map<std::string, std::string>& f,
        const std::vector<std::string>& a)
        : object(obj), flags(f), args(a) {
    }

    void execute(Presentation& presentation) override;
    std::string getName() const override;

protected:
    void validate() const override;
};

#endif // !SAVE_COMMAND_H_