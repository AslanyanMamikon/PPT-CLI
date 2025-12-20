#ifndef IACTION_H_
#define IACTION_H_

#include <memory>

class Presentation;

class IAction {
public:
    virtual ~IAction() = default;

    virtual void execute(Presentation& presentation) = 0;
    virtual std::unique_ptr<IAction> createInverse() = 0;
};

#endif // IACTION_H_