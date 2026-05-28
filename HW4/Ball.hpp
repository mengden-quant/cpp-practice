#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
    Ball() = default;
    inline Ball(double radius, Color color, bool collidable) : 
    radius{radius}, color{color}, collidable{collidable} {};
    void setVelocity(const Velocity& newVelocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& newCenter);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool getisCollidable() const;
private:
    Velocity velocity;
    Point center;
    double radius;
    Color color;
    bool collidable;
};
