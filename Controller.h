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
    Controller() = default;

    bool processCommand(std::istream& stream);
    bool processCommand(const std::string& input); // petq kga te che der chgitem 

    const std::string& getLastError() const { return lastError; }
    Presentation& getPresentation() { return presentation; }
    const Presentation& getPresentation() const { return presentation; }
private:
    Presentation presentation;
    std::string lastError;
};

#endif // CONTROLLER_H_