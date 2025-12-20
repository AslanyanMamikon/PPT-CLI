#ifndef SLIDE_ACTIONS_H_
#define SLIDE_ACTIONS_H_

#include "IAction.h"
#include "Presentation.h"
#include "Slide.h"
#include <memory>
#include <string>

// AddSlideAction - Adds a slide to the presentation
class AddSlideAction : public IAction {
private:
    int position;
    std::string text;
    int addedSlideId;

public:
    AddSlideAction(int pos, const std::string& txt);

    void execute(Presentation& presentation) override;
    std::unique_ptr<IAction> createInverse() override;
};

// RemoveSlideAction - Removes a slide from the presentation
class RemoveSlideAction : public IAction {
private:
    int position;                           // Position to remove from
    std::unique_ptr<Slide> removedSlide;    // Snapshot of removed slide

public:
    explicit RemoveSlideAction(int pos);

    void execute(Presentation& presentation) override;
    std::unique_ptr<IAction> createInverse() override;
};

// RestoreSlideAction - Restores a previously removed slide
class RestoreSlideAction : public IAction {
private:
    int position;
    std::unique_ptr<Slide> slideToRestore;

public:
    RestoreSlideAction(int pos, std::unique_ptr<Slide> slide);

    void execute(Presentation& presentation) override;
    std::unique_ptr<IAction> createInverse() override;
};

// MoveSlideAction - Moves a slide from one position to another
class MoveSlideAction : public IAction {
private:
    int fromPosition;
    int toPosition;

public:
    MoveSlideAction(int from, int to);

    void execute(Presentation& presentation) override;
    std::unique_ptr<IAction> createInverse() override;
};

#endif // SLIDE_ACTIONS_H_