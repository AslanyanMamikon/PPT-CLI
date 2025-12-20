#ifndef IBRUSH_H_
#define IBRUSH_H_

#include <string>
#include <memory>

// Interface for brush - used for filling shapes
class IBrush {
public:
    virtual ~IBrush() = default;

    virtual std::string getColor() const = 0;
    virtual void setColor(const std::string& color) = 0;

    virtual double getOpacity() const = 0;
    virtual void setOpacity(double opacity) = 0; // 0.0 to 1.0

    virtual std::string getPattern() const = 0; // "solid", "gradient", "pattern"
    virtual void setPattern(const std::string& pattern) = 0;

    virtual std::unique_ptr<IBrush> clone() const = 0;
};

// Concrete implementation of brush
class Brush : public IBrush {
private:
    std::string color;
    double opacity;
    std::string pattern;

public:
    Brush(const std::string& color = "white",
        double opacity = 1.0,
        const std::string& pattern = "solid")
        : color(color), opacity(opacity), pattern(pattern) {
    }

    std::string getColor() const override { return color; }
    void setColor(const std::string& c) override { color = c; }

    double getOpacity() const override { return opacity; }
    void setOpacity(double op) override { opacity = op; }

    std::string getPattern() const override { return pattern; }
    void setPattern(const std::string& p) override { pattern = p; }

    std::unique_ptr<IBrush> clone() const override {
        return std::make_unique<Brush>(*this);
    }
};

#endif // IBRUSH_H_