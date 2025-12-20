#include "SlideActions.h"
#include <iostream>

// AddSlideAction Implementation
AddSlideAction::AddSlideAction(int pos, const std::string& txt)
    : position(pos), text(txt), addedSlideId(-1) {
}

void AddSlideAction::execute(Presentation& presentation) {
    if (position == -1 || position > static_cast<int>(presentation.size())) {
        // Add at end
        Slide& slide = presentation.addSlide(text);
        addedSlideId = slide.getId();
        position = static_cast<int>(presentation.size());
        std::cout << "Added slide at position " << position
            << " with ID: " << addedSlideId << "\n";
    }
    else {
        // Add at specific position
        presentation.addSlideAtPosition(position, text);
        Slide* slide = presentation.getSlideAtPosition(position);
        if (slide) {
            addedSlideId = slide->getId();
        }
        std::cout << "Added slide at position " << position << "\n";
    }
}

std::unique_ptr<IAction> AddSlideAction::createInverse() {
    // Inverse of adding a slide is removing it
    return std::make_unique<RemoveSlideAction>(position);
}

// RemoveSlideAction Implementation
RemoveSlideAction::RemoveSlideAction(int pos)
    : position(pos), removedSlide(nullptr) {
}

void RemoveSlideAction::execute(Presentation& presentation) {
    // Save the slide before removing
    Slide* slide = presentation.getSlideAtPosition(position);
    if (slide) {
        removedSlide = std::make_unique<Slide>(*slide);
    }

    // Remove the slide
    presentation.removeSlideAtPosition(position);
    std::cout << "Removed slide at position " << position << "\n";
}

std::unique_ptr<IAction> RemoveSlideAction::createInverse() {
    // Inverse of removing a slide is adding it back
    if (!removedSlide) {
        throw std::runtime_error("Cannot create inverse: no slide snapshot");
    }
    return std::make_unique<RestoreSlideAction>(position, std::move(removedSlide));
}

// RestoreSlideAction Implementation
RestoreSlideAction::RestoreSlideAction(int pos, std::unique_ptr<Slide> slide)
    : position(pos), slideToRestore(std::move(slide)) {
}

void RestoreSlideAction::execute(Presentation& presentation) {
    if (!slideToRestore) {
        throw std::runtime_error("Cannot restore: no slide to restore");
    }

    // Add the slide back at its original position
    std::string text = slideToRestore->getText();
    presentation.addSlideAtPosition(position, text);

    // Copy all objects from the saved slide
    Slide* restoredSlide = presentation.getSlideAtPosition(position);
    if (restoredSlide) {
        for (const auto& obj : slideToRestore->getObjects()) {
            restoredSlide->addObject(obj->clone());
        }
    }

    std::cout << "Restored slide at position " << position << "\n";
}

std::unique_ptr<IAction> RestoreSlideAction::createInverse() {
    // Inverse of restoring a slide is removing it
    return std::make_unique<RemoveSlideAction>(position);
}

// MoveSlideAction Implementation
MoveSlideAction::MoveSlideAction(int from, int to)
    : fromPosition(from), toPosition(to) {
}

void MoveSlideAction::execute(Presentation& presentation) {
    presentation.moveSlide(fromPosition, toPosition);
    std::cout << "Moved slide from position " << fromPosition
        << " to position " << toPosition << "\n";
}

std::unique_ptr<IAction> MoveSlideAction::createInverse() {
    // Inverse is moving it back
    return std::make_unique<MoveSlideAction>(toPosition, fromPosition);
}