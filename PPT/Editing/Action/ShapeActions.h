#ifndef SHAPE_ACTIONS_H_
#define SHAPE_ACTIONS_H_

#include "IAction.h"
#include "Presentation.h"
#include "SlideObject.h"
#include <memory>
#include <string>

// AddShapeAction
class AddShapeAction : public IAction {
private:
    int slidePosition;
    std::unique_ptr<SlideObject> shapeToAdd;
    std::string shapeName;

public:
    AddShapeAction(int slidePos, std::unique_ptr<SlideObject> shape);

    void execute(Presentation& presentation) override;
    std::unique_ptr<IAction> createInverse() override;
};

// RemoveShapeAction
class RemoveShapeAction : public IAction {
private:
    int slidePosition;
    std::string shapeName;
    std::unique_ptr<SlideObject> removedShape;

public:
    RemoveShapeAction(int slidePos, const std::string& name);

    void execute(Presentation& presentation) override;
    std::unique_ptr<IAction> createInverse() override;
};

#endif // SHAPE_ACTIONS_H_