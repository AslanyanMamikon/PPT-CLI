#ifndef ADD_SHAPE_COMMAND_H_
#define ADD_SHAPE_COMMAND_H_

#include "ICommand.h"
#include "Editor.h"
#include "ShapeActions.h"
#include "Argument.h"
#include "SlideObject.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <memory>

class AddShapeCommand : public ICommand {
private:
    std::string object;
    std::unordered_map<std::string, std::string> flags;
    std::vector<std::string> args;
    Editor& editor;

    std::unique_ptr<SlideObject> createShape();
    std::string getFlag(const std::string& flagName,
        const std::string& defaultValue) const;

public:
    AddShapeCommand(const std::string& obj,
        const std::unordered_map<std::string, std::string>& f,
        const std::vector<std::string>& a,
        Editor& ed)
        : object(obj), flags(f), args(a), editor(ed) {
    }

    void execute(Presentation& presentation) override;
    std::string getName() const override;

protected:
    void validate() const override;
};

#endif // ADD_SHAPE_COMMAND_H_