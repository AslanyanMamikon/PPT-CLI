#include "SVGCanvas.h"

SVGCanvas::SVGCanvas(size_t w, size_t h,
    const std::string& bgColor,
    bool grid, size_t gridSpace)
    : width(w), height(h), backgroundColor(bgColor),
    includeGrid(grid), gridSpacing(gridSpace) {}

std::string SVGCanvas::escapeXML(const std::string& str) const {
    std::ostringstream oss;
    for (char c : str) {
        switch (c) {
        case '&': oss << "&amp;"; break;
        case '<': oss << "&lt;"; break;
        case '>': oss << "&gt;"; break;
        case '"': oss << "&quot;"; break;
        case '\'': oss << "&apos;"; break;
        default: oss << c; break;
        }
    }
    return oss.str();
}

std::string SVGCanvas::getPenStrokeAttributes(const IPen& pen) const {
    std::ostringstream oss;
    oss << "stroke=\"" << pen.getColor() << "\" ";
    oss << "stroke-width=\"" << pen.getWidth() << "\"";

    if (pen.getStyle() == "dashed") {
        oss << " stroke-dasharray=\"5,5\"";
    }
    else if (pen.getStyle() == "dotted") {
        oss << " stroke-dasharray=\"2,2\"";
    }

    return oss.str();
}

std::string SVGCanvas::getBrushFillAttributes(const IBrush& brush) const {
    std::ostringstream oss;
    oss << "fill=\"" << brush.getColor() << "\"";

    if (brush.getOpacity() < 1.0) {
        oss << " fill-opacity=\"" << brush.getOpacity() << "\"";
    }

    return oss.str();
}

std::string SVGCanvas::generateHeader() const {
    std::ostringstream oss;

    // SVG header
    oss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    oss << "<svg xmlns=\"http://www.w3.org/2000/svg\" "
        << "width=\"" << width << "\" "
        << "height=\"" << height << "\" "
        << "viewBox=\"0 0 " << width << " " << height << "\">\n";

    // Background rectangle
    oss << "  <rect width=\"100%\" height=\"100%\" fill=\""
        << backgroundColor << "\"/>\n";

    // Optional grid
    if (includeGrid) {
        oss << "  <g id=\"grid\" stroke=\"#e0e0e0\" stroke-width=\"1\" opacity=\"0.5\">\n";
        for (size_t x = 0; x <= width; x += gridSpacing) {
            oss << "    <line x1=\"" << x << "\" y1=\"0\" "
                << "x2=\"" << x << "\" y2=\"" << height << "\"/>\n";
        }
        for (size_t y = 0; y <= height; y += gridSpacing) {
            oss << "    <line x1=\"0\" y1=\"" << y << "\" "
                << "x2=\"" << width << "\" y2=\"" << y << "\"/>\n";
        }
        oss << "  </g>\n";
    }

    return oss.str();
}

void SVGCanvas::drawLine(size_t x1, size_t y1, size_t x2, size_t y2,
    const IPen& pen) {
    content << "  <line "
        << "x1=\"" << x1 << "\" "
        << "y1=\"" << y1 << "\" "
        << "x2=\"" << x2 << "\" "
        << "y2=\"" << y2 << "\" "
        << getPenStrokeAttributes(pen) << "/>\n";
}

void SVGCanvas::drawRectangle(const Geometry& geom,
    const IPen& pen,
    const IBrush& brush) {
    Point tl = geom.getTopLeft();
    content << "  <rect "
        << "x=\"" << tl.x << "\" "
        << "y=\"" << tl.y << "\" "
        << "width=\"" << geom.getWidth() << "\" "
        << "height=\"" << geom.getHeight() << "\" "
        << getBrushFillAttributes(brush) << " "
        << getPenStrokeAttributes(pen) << "/>\n";
}

void SVGCanvas::drawCircle(size_t centerX, size_t centerY, size_t radius,
    const IPen& pen,
    const IBrush& brush) {
    content << "  <circle "
        << "cx=\"" << centerX << "\" "
        << "cy=\"" << centerY << "\" "
        << "r=\"" << radius << "\" "
        << getBrushFillAttributes(brush) << " "
        << getPenStrokeAttributes(pen) << "/>\n";
}

void SVGCanvas::drawText(size_t x, size_t y,
    const std::string& text,
    const std::string& font,
    size_t fontSize,
    const std::string& color,
    const std::string& alignment) {
    content << "  <text "
        << "x=\"" << x << "\" "
        << "y=\"" << y << "\" "
        << "font-family=\"" << font << "\" "
        << "font-size=\"" << fontSize << "\" "
        << "fill=\"" << color << "\" "
        << "text-anchor=\"" << alignment << "\">"
        << escapeXML(text)
        << "</text>\n";
}

void SVGCanvas::clear() {
    content.str("");
    content.clear();
}

std::string SVGCanvas::getContent() const {
    std::ostringstream result;

    // Generate complete SVG
    result << generateHeader();
    result << content.str();
    result << "</svg>\n";

    return result.str();
}

void SVGCanvas::setBackground(const std::string& color) {
    backgroundColor = color;
}

size_t SVGCanvas::getWidth() const {
    return width;
}

size_t SVGCanvas::getHeight() const {
    return height;
}

void SVGCanvas::setIncludeGrid(bool grid) {
    includeGrid = grid;
}

void SVGCanvas::setGridSpacing(size_t spacing) {
    gridSpacing = spacing;
}