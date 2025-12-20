#ifndef APEN_H_
#define APEN_H_

#include <string>
#include <memory>

// Interface for pen
class IPen {
public:
    virtual ~IPen() = default;

    virtual std::string getColor() const = 0;
    virtual void setColor(const std::string& color) = 0;

    virtual size_t getWidth() const = 0;
    virtual void setWidth(size_t width) = 0;

    virtual std::string getStyle() const = 0; // "solid", "dashed", "dotted"
    virtual void setStyle(const std::string& style) = 0;

    virtual std::unique_ptr<IPen> clone() const = 0;
};

// Concrete implementation of pen
class Pen : public IPen {
private:
    std::string color;
    size_t width;
    std::string style;

public:
    Pen(const std::string& color = "black",
        size_t width = 1,
        const std::string& style = "solid")
        : color(color), width(width), style(style) {
    }

    std::string getColor() const override { return color; }
    void setColor(const std::string& c) override { color = c; }

    size_t getWidth() const override { return width; }
    void setWidth(size_t w) override { width = w; }

    std::string getStyle() const override { return style; }
    void setStyle(const std::string& s) override { style = s; }

    std::unique_ptr<IPen> clone() const override {
        return std::make_unique<Pen>(*this);
    }
};

#endif // APEN_H_