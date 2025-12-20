#ifndef RENDER_COMMAND_H_
#define RENDER_COMMAND_H_

#include "ICommand.h"
#include "Argument.h"
#include "Presentation.h"
#include "SVGCanvas.h"
#include "SVGPainter.h"
#include <fstream>
#include <filesystem>
#include <iomanip>

class RenderSlideCommand : public ICommand {
private:
    std::string object;
    std::unordered_map<std::string, std::string> flags;
    std::vector<std::string> args;

public:
    RenderSlideCommand(const std::string& obj,
        const std::unordered_map<std::string, std::string>& f,
        const std::vector<std::string>& a)
        : object(obj), flags(f), args(a) {
    }

    void execute(Presentation& presentation) override;
    std::string getName() const override;

protected:
    void validate() const override;
};

class RenderPresentationCommand : public ICommand {
private:
    std::string object;
    std::unordered_map<std::string, std::string> flags;
    std::vector<std::string> args;

public:
    RenderPresentationCommand(const std::string& obj,
        const std::unordered_map<std::string, std::string>& f,
        const std::vector<std::string>& a)
        : object(obj), flags(f), args(a) {
    }

    void execute(Presentation& presentation) override;
    std::string getName() const override;

protected:
    void validate() const override;
};


class ShowSlideCommand : public ICommand {
private:
    std::string object;
    std::unordered_map<std::string, std::string> flags;
    std::vector<std::string> args;

public:
    ShowSlideCommand(const std::string& obj,
        const std::unordered_map<std::string, std::string>& f,
        const std::vector<std::string>& a)
        : object(obj), flags(f), args(a) {
    }

    void execute(Presentation& presentation) override;
    std::string getName() const override;

protected:
    void validate() const override;
};

#endif // RENDER_COMMAND_H_