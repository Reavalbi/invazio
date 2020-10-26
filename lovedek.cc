#include "lovedek.h"

lovedek::lovedek(int r, float x, float y) : r{r}, x{x}, y{y} {}

void lovedek::mozdit(float dy, float dx) {
  y += dy;
  x += dx;
}

bool lovedek::talalat_vizsgalat(lovedek const& l) {
  return std::pow(l.x - x, 2) + std::pow(l.y - y, 2) < std::pow(r + l.r, 2);
}

void lovedek::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  sf::CircleShape circle;
  circle.setRadius(r);
  circle.setOutlineColor(sf::Color::Green);
  circle.setFillColor(sf::Color::Black);
  circle.setOutlineThickness(4);
  circle.setPosition(x, y);
  target.draw(circle);
}
