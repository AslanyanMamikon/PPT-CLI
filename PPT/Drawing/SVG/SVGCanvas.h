#ifndef SVG_CANVAS_H_
#define SVG_CANVAS_H_

#include "ICanvas.h"
#include <sstream>
#include <vector>
#include <string>

// SVG-specific canvas implementation
class SVGCanvas : public ICanvas {
private:
    size_t width;
    size_t height;
    std::string backgroundColor;
    std::ostringstream content;  // Stores only the objects, not header/footer
    bool includeGrid;
    size_t gridSpacing;

    std::string escapeXML(const std::string& str) const;
    std::string getPenStrokeAttributes(const IPen& pen) const;
    std::string getBrushFillAttributes(const IBrush& brush) const;
    std::string generateHeader() const;

public:
    SVGCanvas(size_t w = 1920, size_t h = 1080,
        const std::string& bgColor = "white",
        bool grid = false, size_t gridSpace = 50);

    void drawLine(size_t x1, size_t y1, size_t x2, size_t y2,
        const IPen& pen) override;

    void drawRectangle(const Geometry& geom,
        const IPen& pen,
        const IBrush& brush) override;

    void drawCircle(size_t centerX, size_t centerY, size_t radius,
        const IPen& pen,
        const IBrush& brush) override;

    void drawText(size_t x, size_t y,
        const std::string& text,
        const std::string& font,
        size_t fontSize,
        const std::string& color,
        const std::string& alignment = "start") override;

    void clear() override;
    std::string getContent() const override;
    void setBackground(const std::string& color) override;

    size_t getWidth() const override;
    size_t getHeight() const override;

    void setIncludeGrid(bool grid);
    void setGridSpacing(size_t spacing);
};

#endif // SVG_CANVAS_H_