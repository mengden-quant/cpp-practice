#pragma once
#include "Ball.hpp"
#include "Color.hpp"
#include "Point.hpp"
#include <vector>

struct Collision {
  Point point;
  double radius;
  Color color;
  double velocity;
};

class Physics {
  public:
    Physics(double timePerTick = 0.001);
    void setWorldBox(const Point& topLeft, const Point& bottomRight);
    std::vector<Collision> update(std::vector<Ball>& balls, size_t ticks) const;
    std::vector<Collision> collideBalls(std::vector<Ball>& balls) const;

  private:
   // void collideBalls(std::vector<Ball>& balls) const;
    void collideWithBox(std::vector<Ball>& balls) const;
    void move(std::vector<Ball>& balls) const;
    void processCollision(Ball& a, Ball& b,
                          double distanceBetweenCenters2) const;

  private:
    Point topLeft;
    Point bottomRight;
    double timePerTick;
};
