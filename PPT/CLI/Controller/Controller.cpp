#include "Controller.h"
#include "Parser.h"

Controller::Controller() : shouldExit(false) {}

void Controller::run() {
    std::cout << "Presentation CLI (Action-based Architecture)\n";
    std::cout << "Commands: add slide, remove slide, list, undo, redo, exit\n\n";

    std::string line;
    while (!shouldExit) {
        std::cout << "(ppt) > ";
        std::getline(std::cin, line);

        if (line.empty()) {
            continue;
        }

        if (!processCommand(line)) {
            std::cerr << "Error: " << lastError << "\n";
        }
    }
}

bool Controller::processCommand(std::istream& stream) {
    lastError.clear();

    try {
        Parser parser(stream);

        std::unique_ptr<ICommand> command = parser.parse(&shouldExit, &editor);

        if (!command) {
            lastError = parser.getError();
            return false;
        }

        command->execute(editor.getPresentation());

        return true;
    }
    catch (const CommandValidationException& e) {
        lastError = std::string("Validation error: ") + e.what();
        return false;
    }
    catch (const std::exception& e) {
        lastError = std::string("Error: ") + e.what();
        return false;
    }
}

bool Controller::processCommand(const std::string& input) {
    std::istringstream stream(input);
    return processCommand(stream);
}

const std::string& Controller::getLastError() const { return lastError; }
Editor& Controller::getEditor() { return editor; }
const Editor& Controller::getEditor() const { return editor; }
Presentation& Controller::getPresentation() { return editor.getPresentation(); }
bool Controller::shouldExitProgram() const { return shouldExit; }