#include "Dust.hpp"
#include <cmath>

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Dust::setVelocity(const Velocity& newVelocity) {
    velocity = newVelocity;
}

Velocity Dust::getVelocity() const {
    return velocity;
}

void Dust::draw(Painter& painter) const {
    painter.draw(center, radius, color);
}

void Dust::setCenter(const Point& newCenter) {
    center = newCenter;
}

Point Dust::getCenter() const {
    return center;
}

double Dust::getRadius() const {
    return radius;
}

void Dust::move(double time) {
    const Point newCenter = center + velocity.vector() * time;
    center = newCenter;
    lifetime -= time;
}

bool Dust::isAlive() const {
    return lifetime > 0.0;
}
