#include "Presentation.h"

Slide& Presentation::addSlide(const std::string& text)
{
    int newId = getNextId();
    slides.push_back(std::make_unique<Slide>(newId, text));
    return *slides.back();
}

void Presentation::addSlideAtPosition(int pos, const std::string& text)
{
    if (pos < 1 || pos > static_cast<int>(slides.size()) + 1)
        throw std::runtime_error("Invalid position: " + std::to_string(pos) +
            ". Valid range: 1-" + std::to_string(slides.size() + 1));

    int newId = getNextId();
    auto newSlide = std::make_unique<Slide>(newId, text);
    if (pos > static_cast<int>(slides.size())) {
        slides.push_back(std::move(newSlide));
    }
    else {
        slides.insert(slides.begin() + pos - 1, std::move(newSlide));
    }
}

Slide* Presentation::getSlideById(int id)
{
    for (auto& slide : slides) {
        if (slide->getId() == id)
            return slide.get();
    }
    return nullptr;
}

Slide* Presentation::getSlideAtPosition(int pos)
{
    if (pos < 1 || pos > static_cast<int>(slides.size()))
        return nullptr;

    return slides[pos - 1].get();
}

bool Presentation::hasSlide(int id) const
{
    for (const auto& slide : slides)
    {
        if (slide->getId() == id)
            return true;
    }
    return false;
}

void Presentation::removeSlide(int id)
{
    slides.erase(std::remove_if(slides.begin(), slides.end(),
        [id](const std::unique_ptr<Slide>& s) { return s->getId() == id; }),
        slides.end());
}

void Presentation::removeSlideAtPosition(int pos)
{
    validatePosition(pos);
    slides.erase(slides.begin() + pos - 1);
}

void Presentation::removeLastSlide()
{
    if (slides.empty())
        throw std::runtime_error("Can't remove slide: presentation is empty");
    slides.pop_back();
}

void Presentation::listSlides() const
{
    std::cout << "Presentation contains " << slides.size() << " slides:\n";
    for (size_t i = 0; i < slides.size(); ++i) {
        std::cout << "Position " << (i + 1) << ": ";
        slides[i]->display();
    }
}

void Presentation::moveSlide(int from, int to)
{
    validatePosition(from);
    if (to < 1 || to > static_cast<int>(slides.size())) {
        throw std::runtime_error("Invalid target position: " + std::to_string(to));
    }

    auto slide = std::move(slides[from - 1]);
    slides.erase(slides.begin() + from - 1);
    slides.insert(slides.begin() + to - 1, std::move(slide));
}

void Presentation::duplicateSlide(int pos)
{
    validatePosition(pos);

    Slide* original = slides[pos - 1].get();
    auto duplicate = std::make_unique<Slide>(*original);

    int newId = getNextId();
    duplicate->setId(newId);

    slides.insert(slides.begin() + pos, std::move(duplicate));
}

size_t Presentation::size() const { return slides.size(); }

void Presentation::validatePosition(int pos) const
{
    if (pos < 1 || pos > static_cast<int>(slides.size()))
        throw std::runtime_error("Invalid position: " + std::to_string(pos) +
            ". Valid range: 1-" + std::to_string(slides.size()));
}

int Presentation::getNextId() const
{
    int maxId = 0;
    for (const auto& slide : slides) {
        if (slide->getId() > maxId)
            maxId = slide->getId();
    }
    return maxId + 1;
}

const Slide* Presentation::getSlideAtPosition(int pos) const
{
    if (pos < 1 || pos > static_cast<int>(slides.size()))
        return nullptr;

    return slides[pos - 1].get();
}