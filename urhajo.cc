#include "urhajo.h"

urhajo::urhajo(float w, float h, float x, float y)
    : w{w}, h{h}, x{x}, y{y}, eltalalt{false} {}

bool urhajo::talalat_vizsgalat(lovedek const& l) {
  float lkx = l.x + l.r;
  float lky = l.y + l.r;
  float vr = l.r / 2;
  float x1 = x - w / 2;
  float x2 = x + w / 2;
  float y1 = y;
  float y2 = y + h;
  bool eredmeny = false;
  if (lky < y2 + vr && lky > y1 - vr && lkx < x2 + vr && lkx > x1 - vr) {
    eredmeny = true;
    eltalalt = true;
  }
  return eredmeny;
}

void urhajo::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(w, h));
  rectangle.setOutlineColor(sf::Color::Red);
  rectangle.setOutlineThickness(0);
  rectangle.setPosition(x - w / 2, y);
  target.draw(rectangle);
}
