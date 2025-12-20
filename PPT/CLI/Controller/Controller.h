#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "Editor.h"
#include "Parser.h"
#include "ICommand.h"
#include "CommandFactory.h"
#include <iostream>
#include <memory>
#include <sstream>

class Controller {
private:
    Editor editor;
    std::string lastError;
    bool shouldExit;

public:
    Controller();

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