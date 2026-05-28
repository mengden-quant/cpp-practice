#include "Color.hpp"
#include <istream>

Color::Color() = default;

Color::Color(double red, double green, double blue)
    : r{red}, g{green}, b{blue} {}

double Color::red() const {
    return r;
}

double Color::green() const {
    return g;
}

double Color::blue() const {
    return b;
}

std::istream& operator>>(std::istream& stream, Color& color) {
    double red;
    double green;
    double blue;
    stream >> red >> green >> blue;
    color = Color{red, green, blue};
    return stream;
}
