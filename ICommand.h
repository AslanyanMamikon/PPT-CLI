#ifndef ICOMMAND_H_
#define ICOMMAND_H_

#include <memory>
#include <string>
#include <stdexcept>

class Presentation; 

class CommandValidationException : public std::runtime_error {
public:
    explicit CommandValidationException(const std::string& msg)
        : std::runtime_error(msg) {}
};

class ICommand {
public:
    virtual ~ICommand() = default;

    virtual void execute(Presentation& presentation) = 0;
    virtual std::string getName() const = 0;

protected:
    //virtual void validate() const = 0;
};

#endif // ICOMMAND_H_