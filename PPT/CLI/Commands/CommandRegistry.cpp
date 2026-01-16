#include "CommandRegistry.h"
#include "AddSlideCommand.h"
#include "RemoveSlideCommand.h"
#include "MoveSlideCommand.h"
#include "AddShapeCommand.h"
#include "RemoveShapeCommand.h"
#include "ListCommand.h"
#include "DuplicateCommand.h"
#include "SaveCommand.h"
#include "UndoRedoCommands.h"
#include "ExitCommand.h"
#include "RenderCommand.h"

// Command creator functions
namespace CommandCreators {
    std::unique_ptr<ICommand> createAddSlide(
        const std::string& object,
        const std::unordered_map<std::string, std::string>& flags,
        const std::vector<std::string>& args,
        bool* exitFlag,
        Editor* editor) {

        if (!editor) return nullptr;
        return std::make_unique<AddSlideCommand>(object, flags, args, *editor);
    }

    std::unique_ptr<ICommand> createRemoveSlide(
        const std::string& object,
        const std::unordered_map<std::string, std::string>& flags,
        const std::vector<std::string>& args,
        bool* exitFlag,
        Editor* editor) {

        if (!editor) return nullptr;
        return std::make_unique<RemoveSlideCommand>(object, flags, args, *editor);
    }

    std::unique_ptr<ICommand> createMoveSlide(
        const std::string& object,
        const std::unordered_map<std::string, std::string>& flags,
        const std::vector<std::string>& args,
        bool* exitFlag,
        Editor* editor) {

        if (!editor) return nullptr;
        return std::make_unique<MoveSlideCommand>(object, flags, args, *editor);
    }

    std::unique_ptr<ICommand> createAddShape(
        const std::string& object,
        const std::unordered_map<std::string, std::string>& flags,
        const std::vector<std::string>& args,
        bool* exitFlag,
        Editor* editor) {

        if (!editor) return nullptr;
        return std::make_unique<AddShapeCommand>(object, flags, args, *editor);
    }

    std::unique_ptr<ICommand> createRemoveShape(
        const std::string& object,
        const std::unordered_map<std::string, std::string>& flags,
        const std::vector<std::string>& args,
        bool* exitFlag,
        Editor* editor) {

        if (!editor) return nullptr;
        return std::make_unique<RemoveShapeCommand>(object, flags, args, *editor);
    }

    std::unique_ptr<ICommand> createList(
        const std::string& object,
        const std::unordered_map<std::string, std::string>& flags,
        const std::vector<std::string>& args,
        bool* exitFlag,
        Editor* editor) {

        return std::make_unique<ListSlidesCommand>(object, flags, args);
    }

    std::unique_ptr<ICommand> createDuplicate(
        const std::string& object,
        const std::unordered_map<std::string, std::string>& flags,
        const std::vector<std::string>& args,
        bool* exitFlag,
        Editor* editor) {

        return std::make_unique<DuplicateSlideCommand>(object, flags, args);
    }

    std::unique_ptr<ICommand> createSave(
        const std::string& object,
        const std::unordered_map<std::string, std::string>& flags,
        const std::vector<std::string>& args,
        bool* exitFlag,
        Editor* editor) {

        return std::make_unique<SaveCommand>(object, flags, args);
    }

    std::unique_ptr<ICommand> createLoad(
        const std::string& object,
        const std::unordered_map<std::string, std::string>& flags,
        const std::vector<std::string>& args,
        bool* exitFlag,
        Editor* editor) {

        return std::make_unique<LoadCommand>(object, flags, args);
    }

    std::unique_ptr<ICommand> createUndo(
        const std::string& object,
        const std::unordered_map<std::string, std::string>& flags,
        const std::vector<std::string>& args,
        bool* exitFlag,
        Editor* editor) {

        if (!editor) return nullptr;
        return std::make_unique<UndoCommand>(*editor);
    }

    std::unique_ptr<ICommand> createRedo(
        const std::string& object,
        const std::unordered_map<std::string, std::string>& flags,
        const std::vector<std::string>& args,
        bool* exitFlag,
        Editor* editor) {

        if (!editor) return nullptr;
        return std::make_unique<RedoCommand>(*editor);
    }

    std::unique_ptr<ICommand> createExit(
        const std::string& object,
        const std::unordered_map<std::string, std::string>& flags,
        const std::vector<std::string>& args,
        bool* exitFlag,
        Editor* editor) {

        if (!exitFlag) return nullptr;
        return std::make_unique<ExitCommand>(object, flags, args, *exitFlag);
    }

    std::unique_ptr<ICommand> createRenderSlide(
        const std::string& object,
        const std::unordered_map<std::string, std::string>& flags,
        const std::vector<std::string>& args,
        bool* exitFlag,
        Editor* editor) {

        return std::make_unique<RenderSlideCommand>(object, flags, args);
    }

    std::unique_ptr<ICommand> createRenderPresentation(
        const std::string& object,
        const std::unordered_map<std::string, std::string>& flags,
        const std::vector<std::string>& args,
        bool* exitFlag,
        Editor* editor) {

        return std::make_unique<RenderPresentationCommand>(object, flags, args);
    }

    std::unique_ptr<ICommand> createShowSlide(
        const std::string& object,
        const std::unordered_map<std::string, std::string>& flags,
        const std::vector<std::string>& args,
        bool* exitFlag,
        Editor* editor) {

        return std::make_unique<ShowSlideCommand>(object, flags, args);
    }
}

CommandRegistry::CommandRegistry() {
    registerAllCommands();
}

void CommandRegistry::registerCommand(std::shared_ptr<IMetaCommand> metaCmd) {
    if (metaCmd) {
        commands[metaCmd->getName()] = metaCmd;
    }
}

std::shared_ptr<IMetaCommand> CommandRegistry::findMetaCommand(const std::string& name) const {
    auto it = commands.find(name);
    return (it != commands.end()) ? it->second : nullptr;
}

std::vector<std::shared_ptr<IMetaCommand>> CommandRegistry::getAllMetaCommands() const {
    std::vector<std::shared_ptr<IMetaCommand>> result;
    result.reserve(commands.size());

    for (const auto& pair : commands) {
        result.push_back(pair.second);
    }

    return result;
}

std::unique_ptr<ICommand> CommandRegistry::createCommand(
    const std::string& cmdName,
    const std::string& object,
    const std::unordered_map<std::string, std::string>& flags,
    const std::vector<std::string>& args,
    bool* exitFlag,
    Editor* editor) const {

    auto metaCmd = findMetaCommand(cmdName);
    if (metaCmd) {
        return metaCmd->createCommand(object, flags, args, exitFlag, editor);
    }

    return nullptr;
}

bool CommandRegistry::hasCommand(const std::string& name) const {
    return commands.find(name) != commands.end();
}

size_t CommandRegistry::size() const {
    return commands.size();
}

void CommandRegistry::registerAllCommands() {
    // Add Slide command
    {
        auto meta = std::make_shared<MetaCommand>(
            "add slide",
            "Add a new slide to the presentation",
            CommandCreators::createAddSlide
        );
        meta->addArgument(MetaArgumentInfo("slide", true, ""));
        meta->addArgument(MetaArgumentInfo("-text", false, "blank"));
        meta->addArgument(MetaArgumentInfo("-pos", false, ""));
        registerCommand(meta);
    }

    // Remove Slide command
    {
        auto meta = std::make_shared<MetaCommand>(
            "remove slide",
            "Remove a slide from the presentation",
            CommandCreators::createRemoveSlide
        );
        meta->addArgument(MetaArgumentInfo("slide", true, ""));
        meta->addArgument(MetaArgumentInfo("-pos", false, ""));
        registerCommand(meta);
    }

    // Move Slide command
    {
        auto meta = std::make_shared<MetaCommand>(
            "move slide",
            "Move a slide to a different position",
            CommandCreators::createMoveSlide
        );
        meta->addArgument(MetaArgumentInfo("slide", true, ""));
        meta->addArgument(MetaArgumentInfo("-from", true, ""));
        meta->addArgument(MetaArgumentInfo("-to", true, ""));
        registerCommand(meta);
    }

    // Add Shape command
    {
        auto meta = std::make_shared<MetaCommand>(
            "add shape",
            "Add a shape (rectangle, circle, text, line) to a slide",
            CommandCreators::createAddShape
        );
        meta->addArgument(MetaArgumentInfo("shape_type", true, ""));
        meta->addArgument(MetaArgumentInfo("-name", true, ""));
        meta->addArgument(MetaArgumentInfo("-slide", false, "1"));
        meta->addArgument(MetaArgumentInfo("-x", true, ""));
        meta->addArgument(MetaArgumentInfo("-y", true, ""));
        meta->addArgument(MetaArgumentInfo("-width", false, ""));
        meta->addArgument(MetaArgumentInfo("-height", false, ""));
        meta->addArgument(MetaArgumentInfo("-radius", false, ""));
        meta->addArgument(MetaArgumentInfo("-x2", false, ""));
        meta->addArgument(MetaArgumentInfo("-y2", false, ""));
        meta->addArgument(MetaArgumentInfo("-fill", false, "white"));
        meta->addArgument(MetaArgumentInfo("-border", false, "black"));
        meta->addArgument(MetaArgumentInfo("-border-width", false, "1"));
        meta->addArgument(MetaArgumentInfo("-content", false, ""));
        meta->addArgument(MetaArgumentInfo("-font", false, "Arial"));
        meta->addArgument(MetaArgumentInfo("-font-size", false, "12"));
        meta->addArgument(MetaArgumentInfo("-color", false, "black"));
        registerCommand(meta);
    }

    // Remove Shape command
    {
        auto meta = std::make_shared<MetaCommand>(
            "remove shape",
            "Remove a shape from a slide",
            CommandCreators::createRemoveShape
        );
        meta->addArgument(MetaArgumentInfo("shape_type", true, ""));
        meta->addArgument(MetaArgumentInfo("-name", true, ""));
        meta->addArgument(MetaArgumentInfo("-slide", false, "1"));
        registerCommand(meta);
    }

    // List command
    {
        auto meta = std::make_shared<MetaCommand>(
            "list",
            "List all slides in the presentation",
            CommandCreators::createList
        );
        meta->addArgument(MetaArgumentInfo("slides", false, ""));
        registerCommand(meta);
    }

    // Duplicate command
    {
        auto meta = std::make_shared<MetaCommand>(
            "duplicate slide",
            "Duplicate a slide at a specific position",
            CommandCreators::createDuplicate
        );
        meta->addArgument(MetaArgumentInfo("slide", true, ""));
        meta->addArgument(MetaArgumentInfo("-pos", true, ""));
        registerCommand(meta);
    }

    // Save command
    {
        auto meta = std::make_shared<MetaCommand>(
            "save",
            "Save the presentation to a JSON file",
            CommandCreators::createSave
        );
        meta->addArgument(MetaArgumentInfo("filename", false, "presentation.json"));
        meta->addArgument(MetaArgumentInfo("-file", false, ""));
        registerCommand(meta);
    }

    // Load command
    {
        auto meta = std::make_shared<MetaCommand>(
            "load",
            "Load a presentation from a JSON file",
            CommandCreators::createLoad
        );
        meta->addArgument(MetaArgumentInfo("filename", false, ""));
        meta->addArgument(MetaArgumentInfo("-file", false, ""));
        registerCommand(meta);
    }

    // Undo command
    {
        auto meta = std::make_shared<MetaCommand>(
            "undo",
            "Undo the last action",
            CommandCreators::createUndo
        );
        registerCommand(meta);
    }

    // Redo command
    {
        auto meta = std::make_shared<MetaCommand>(
            "redo",
            "Redo the previously undone action",
            CommandCreators::createRedo
        );
        registerCommand(meta);
    }

    // Exit command
    {
        auto meta = std::make_shared<MetaCommand>(
            "exit",
            "Exit the presentation CLI",
            CommandCreators::createExit
        );
        registerCommand(meta);
    }

    // Render Slide command
    {
        auto meta = std::make_shared<MetaCommand>(
            "render slide",
            "Render a slide to an SVG file",
            CommandCreators::createRenderSlide
        );
        meta->addArgument(MetaArgumentInfo("slide", true, ""));
        meta->addArgument(MetaArgumentInfo("-pos", false, "1"));
        meta->addArgument(MetaArgumentInfo("-output", false, ""));
        meta->addArgument(MetaArgumentInfo("-width", false, "1920"));
        meta->addArgument(MetaArgumentInfo("-height", false, "1080"));
        meta->addArgument(MetaArgumentInfo("-grid", false, ""));
        registerCommand(meta);
    }

    // Render Presentation command
    {
        auto meta = std::make_shared<MetaCommand>(
            "render presentation",
            "Render all slides to SVG files",
            CommandCreators::createRenderPresentation
        );
        meta->addArgument(MetaArgumentInfo("presentation", false, ""));
        meta->addArgument(MetaArgumentInfo("-output", false, "slides"));
        meta->addArgument(MetaArgumentInfo("-width", false, "1920"));
        meta->addArgument(MetaArgumentInfo("-height", false, "1080"));
        meta->addArgument(MetaArgumentInfo("-grid", false, ""));
        registerCommand(meta);
    }

    // Show Slide command
    {
        auto meta = std::make_shared<MetaCommand>(
            "show slide",
            "Display a slide's SVG output in the console",
            CommandCreators::createShowSlide
        );
        meta->addArgument(MetaArgumentInfo("slide", true, ""));
        meta->addArgument(MetaArgumentInfo("-pos", false, "1"));
        meta->addArgument(MetaArgumentInfo("-grid", false, ""));
        registerCommand(meta);
    }
}