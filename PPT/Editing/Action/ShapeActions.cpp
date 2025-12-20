#include "ShapeActions.h"
#include <iostream>
#include <algorithm>

// AddShapeAction Implementation
AddShapeAction::AddShapeAction(int slidePos, std::unique_ptr<SlideObject> shape)
    : slidePosition(slidePos),
    shapeToAdd(std::move(shape)),
    shapeName(shapeToAdd ? shapeToAdd->getName() : "") {
}

void AddShapeAction::execute(Presentation& presentation) {
    Slide* slide = presentation.getSlideAtPosition(slidePosition);
    if (!slide) {
        throw std::runtime_error("Slide at position " +
            std::to_string(slidePosition) + " not found");
    }

    if (!shapeToAdd) {
        throw std::runtime_error("No shape to add");
    }

    shapeName = shapeToAdd->getName();
    slide->addObject(std::move(shapeToAdd));

    std::cout << "Added shape '" << shapeName
        << "' to slide at position " << slidePosition << "\n";
}

std::unique_ptr<IAction> AddShapeAction::createInverse() {
    // Inverse of adding a shape is removing it
    return std::make_unique<RemoveShapeAction>(slidePosition, shapeName);
}

// RemoveShapeAction Implementation
RemoveShapeAction::RemoveShapeAction(int slidePos, const std::string& name)
    : slidePosition(slidePos), shapeName(name), removedShape(nullptr) {
}

void RemoveShapeAction::execute(Presentation& presentation) {
    Slide* slide = presentation.getSlideAtPosition(slidePosition);
    if (!slide) {
        throw std::runtime_error("Slide at position " +
            std::to_string(slidePosition) + " not found");
    }

    // Find and save the shape before removing
    auto& objects = const_cast<std::vector<std::unique_ptr<SlideObject>>&>(
        slide->getObjects());

    auto it = std::find_if(objects.begin(), objects.end(),
        [this](const std::unique_ptr<SlideObject>& obj) {
            return obj->getName() == shapeName;
        });

    if (it == objects.end()) {
        throw std::runtime_error("Shape '" + shapeName + "' not found");
    }

    // Save a copy of the shape
    removedShape = (*it)->clone();

    // Remove from slide
    objects.erase(it);

    std::cout << "Removed shape '" << shapeName
        << "' from slide at position " << slidePosition << "\n";
}

std::unique_ptr<IAction> RemoveShapeAction::createInverse() {
    // Inverse of removing a shape is adding it back
    if (!removedShape) {
        throw std::runtime_error("Cannot create inverse: no shape snapshot");
    }
    return std::make_unique<AddShapeAction>(slidePosition,
        removedShape->clone());
}