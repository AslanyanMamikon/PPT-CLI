#ifndef PRESENTATION_H_
#define PRESENTATION_H_

#include "Slide.h"
#include <vector>
#include <memory>
#include <iostream>

class Presentation {
private:
    std::vector<std::unique_ptr<Slide>> slides;

    void validatePosition(int pos) const
    {
        if(pos < 1 || pos > static_cast<int>(slides.size()))
            throw std::runtime_error("Invalid position: " + std::to_string(pos) +
                                    ". Valid range: 1-" + std::to_string(slides.size()));
    }
    
    void reindexSlides()
    {
        for (size_t i = 0; i < slides.size(); i++)
            slides[i]->setId(static_cast<int>(i) + 1);
    }
public:
    Presentation() = default;

    Slide& addSlide(const std::string& text = "blank") {
        int newId = static_cast<int>(slides.size()) + 1;
        slides.push_back(std::make_unique<Slide>(newId, text));
        return *slides.back();
    }

    void addSlideAtPosition(int pos, const std::string& text = "blank")
    {
        if (pos < 1 || pos > static_cast<int>(slides.size()) + 1)
            throw std::runtime_error("Invalid position: " + std::to_string(pos));
        
        int newId = static_cast<int>(slides.size()) + 1;
        auto newSlide = std::make_unique<Slide>(newId, text);
        slides.insert(slides.begin() + pos - 1, std::move(newSlide));
        reindexSlides();
    }

    Slide* getSlideById(int id) {
        for (auto& slide : slides) {
            if (slide->getId() == id)
                return slide.get();
        }
        return nullptr;
    }

    Slide* getSlideAtPosition(int pos) {
        if (pos < 1 || pos > static_cast<int>(slides.size()))
            return nullptr;

        return slides[pos - 1].get();
    }

    bool hasSlide(int id) const
    {
        for (const auto& slide : slides)
        {
            if (slide->getId() == id)
                return true;
        }
        return false;
    }

    void removeSlide(int id) {
        slides.erase(std::remove_if(slides.begin(), slides.end(),
            [id](const std::unique_ptr<Slide>& s) { return s->getId() == id; }),
            slides.end());
        reindexSlides();
    }

    void removeSlideAtPosition(int pos)
    {
        validatePosition(pos);
        slides.erase(slides.begin() + pos - 1);
        // reindexSlides();
    }

    void removeLastSlide()
    {
        if (slides.empty())
            throw std::runtime_error("Can't remove slide: presentation is empty");
        slides.pop_back();
    }

    void listSlides() const {
        std::cout << "Presentation contains " << slides.size() << " slides:\n";
        //for (const auto& slide : slides)
          //  slide->display();
        for (size_t i = 0; i < slides.size(); ++i) {
            std::cout << "Position " << (i + 1) << ": ";
            slides[i]->display();
        }
    }

    size_t size() const { return slides.size(); }
};

#endif // PRESENTATION_H_
