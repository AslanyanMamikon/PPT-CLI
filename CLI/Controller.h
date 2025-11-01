#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <iostream>
#include <memory>
#include <sstream>
#include "Parser.h"
#include "Tokenizer.h"
#include "ICommand.h"
#include "Presentation.h"

class Controller {
public:
    //Controller() = default;
    Controller() : shouldExit(false) {}

    bool processCommand(std::istream& stream);
    bool processCommand(const std::string& input); // petq kga te che ??????

    const std::string& getLastError() const { return lastError; }
    //---------------------------------------------------------------------------
    Presentation& getPresentation() { return presentation; }
    const Presentation& getPresentation() const { return presentation; }

    bool shouldExitProgram() const { return shouldExit; }
    bool& getExitFlag() { return shouldExit; }

private:
    Presentation presentation;  // Controller owns the presentation------------
    std::string lastError;
    bool shouldExit;
};

#endif // CONTROLLER_H_