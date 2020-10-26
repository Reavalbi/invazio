#ifndef SZORNY_H
#define SZORNY_H

#include <SFML/Graphics.hpp>
#include <array>

#include "lovedek.h"

class szorny : public sf::Drawable {
 public:
  szorny(float w, float h, float x, float y);
  bool talalat_vizsgalat(lovedek const& l);
  bool elo();
  bool teljes();
  float bal_oldal() { return x; }
  float jobb_oldal() { return x + w; }
  float alja() { return y + h; }
  float x_kozep() { return x + w / 2; }
  void mozdit(float dx, float dy) {
    x += dx;
    y += dy;
  }

 private:
  float w, h, x, y;
  std::array<std::array<bool, 2>, 2> eltalalt;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif  // SZORNY_H