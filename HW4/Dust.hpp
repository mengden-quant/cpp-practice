#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Dust {
public:
    Dust() = default;
    inline Dust(double radius, Color color) : radius{radius}, color{color} {};
    void setVelocity(const Velocity& newVelocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& newCenter);
    Point getCenter() const;
    double getRadius() const;
    void move(double time);
    bool isAlive() const;

private:
    Velocity velocity;
    Point center;
    double radius;
    Color color;
    double lifetime{1.2};
};
