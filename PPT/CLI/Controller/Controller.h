#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "Editor.h"
#include "ICommand.h"
#include <iostream>
#include <memory>
#include <sstream>

// Forward declarations
class Parser;
class CommandRegistry;

class Controller {
private:
    Editor editor;
    std::string lastError;
    bool shouldExit;
    std::unique_ptr<CommandRegistry> registry;

public:
    Controller();
    ~Controller();  // Need destructor for unique_ptr to incomplete type

    void run();
    bool processCommand(const std::string& input);
    bool processCommand(std::istream& stream);

    const std::string& getLastError() const;
    Editor& getEditor();
    const Editor& getEditor() const;
    Presentation& getPresentation();
    bool shouldExitProgram() const;
};

#endif // CONTROLLER_H_