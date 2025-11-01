#ifndef PRESENTATION_H_
#define PRESENTATION_H_

#include "Slide.h"
#include <vector>
#include <memory>
#include <iostream>

class Presentation {
public:
    Presentation() = default;

    Slide& addSlide(const std::string& text = "blank");
    void addSlideAtPosition(int pos, const std::string& text = "blank");
    Slide* getSlideById(int id);
    Slide* getSlideAtPosition(int pos);
    const Slide* getSlideAtPosition(int pos) const;

    bool hasSlide(int id) const;
    
    void removeSlide(int id);
    void removeSlideAtPosition(int pos);
    void removeLastSlide();

    void listSlides() const;
    void moveSlide(int from, int to);
    void duplicateSlide(int pos);

    size_t size() const;

private:
    void validatePosition(int pos) const;
    void reindexSlides();

private:
    std::vector<std::unique_ptr<Slide>> slides;
};

#endif // PRESENTATION_H_
