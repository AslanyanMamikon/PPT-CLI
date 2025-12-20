#include "RenderCommand.h"

void RenderSlideCommand::execute(Presentation& presentation) {
    validate();

    int pos = 1;
    if (auto it = flags.find("-pos"); it != flags.end()) {
        pos = std::stoi(it->second);
    }

    Slide* slide = presentation.getSlideAtPosition(pos);
    if (!slide) {
        throw CommandValidationException("Slide at position " +
            std::to_string(pos) + " not found");
    }

    size_t width = 1920;
    size_t height = 1080;
    bool includeGrid = false;

    if (auto it = flags.find("-width"); it != flags.end()) {
        width = std::stoul(it->second);
    }
    if (auto it = flags.find("-height"); it != flags.end()) {
        height = std::stoul(it->second);
    }
    if (flags.find("-grid") != flags.end()) {
        includeGrid = true;
    }

    SVGCanvas canvas(width, height, "white", includeGrid);
    SVGPainter painter;

    slide->renderToCanvas(canvas, painter);

    std::string filename;
    if (auto it = flags.find("-output"); it != flags.end()) {
        filename = it->second;
    }
    else {
        filename = "slide_" + std::to_string(slide->getId()) + ".svg";
    }

    if (filename.find(".svg") == std::string::npos) {
        filename += ".svg";
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        throw CommandValidationException("Failed to open file: " + filename);
    }

    file << canvas.getContent();
    file.close();

    std::cout << "Successfully rendered slide to: " << filename << "\n";
}

std::string RenderSlideCommand::getName() const {
    return "render slide";
}

void RenderSlideCommand::validate() const {
    if (object != "slide") {
        throw CommandValidationException("Render command requires 'slide' object");
    }

    ArgumentValidator validator;
    validator.addInfo({ "-pos", ArgumentType::Integer, false, {} });
    validator.addInfo({ "-output", ArgumentType::String, false, {} });
    validator.addInfo({ "-width", ArgumentType::Integer, false, {} });
    validator.addInfo({ "-height", ArgumentType::Integer, false, {} });
    validator.validate(flags);
}

void RenderPresentationCommand::execute(Presentation& presentation) {
    validate();

    if (presentation.size() == 0) {
        throw CommandValidationException("Presentation is empty");
    }

    size_t width = 1920;
    size_t height = 1080;
    bool includeGrid = false;

    if (auto it = flags.find("-width"); it != flags.end()) {
        width = std::stoul(it->second);
    }
    if (auto it = flags.find("-height"); it != flags.end()) {
        height = std::stoul(it->second);
    }
    if (flags.find("-grid") != flags.end()) {
        includeGrid = true;
    }

    std::string outputDir = "slides";
    if (auto it = flags.find("-output"); it != flags.end()) {
        outputDir = it->second;
    }

    std::filesystem::create_directories(outputDir);

    SVGPainter painter;
    Presentation& pres = const_cast<Presentation&>(presentation);

    for (size_t i = 1; i <= presentation.size(); ++i) {
        Slide* slide = pres.getSlideAtPosition(static_cast<int>(i));
        if (!slide) continue;

        SVGCanvas canvas(width, height, "white", includeGrid);
        slide->renderToCanvas(canvas, painter);

        std::ostringstream filename;
        filename << outputDir << "/slide_"
            << std::setfill('0') << std::setw(3) << i << ".svg";

        std::ofstream file(filename.str());
        if (file.is_open()) {
            file << canvas.getContent();
            file.close();
        }
    }

    std::cout << "Successfully rendered presentation: "
        << presentation.size() << " slides in " << outputDir << "/\n";
}

std::string RenderPresentationCommand::getName() const {
    return "render presentation";
}

void RenderPresentationCommand::validate() const {
    if (!object.empty() && object != "presentation" && object != "all") {
        throw CommandValidationException(
            "Render accepts: presentation, all, or no object");
    }

    ArgumentValidator validator;
    validator.addInfo({ "-output", ArgumentType::String, false, {} });
    validator.addInfo({ "-width", ArgumentType::Integer, false, {} });
    validator.addInfo({ "-height", ArgumentType::Integer, false, {} });
    validator.validate(flags);
}

void ShowSlideCommand::execute(Presentation& presentation) {
    validate();

    int pos = 1;
    if (auto it = flags.find("-pos"); it != flags.end()) {
        pos = std::stoi(it->second);
    }

    Slide* slide = presentation.getSlideAtPosition(pos);
    if (!slide) {
        throw CommandValidationException("Slide at position " +
            std::to_string(pos) + " not found");
    }

    bool includeGrid = (flags.find("-grid") != flags.end());
    SVGCanvas canvas(1920, 1080, "white", includeGrid);
    SVGPainter painter;

    slide->renderToCanvas(canvas, painter);

    std::cout << "\n=== Slide #" << slide->getId() << " SVG Output ===\n";
    std::cout << canvas.getContent();
    std::cout << "=== End of SVG ===\n\n";
}

std::string ShowSlideCommand::getName() const {
    return "show slide";
}

void ShowSlideCommand::validate() const {
    if (object != "slide") {
        throw CommandValidationException("Show requires 'slide' object");
    }

    ArgumentValidator validator;
    validator.addInfo({ "-pos", ArgumentType::Integer, false, {} });
    validator.validate(flags);
}