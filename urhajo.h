#ifndef URHAJO_H
#define URHAJO_H

#include <SFML/Graphics.hpp>

#include "lovedek.h"

class urhajo : public sf::Drawable {
 public:
  urhajo(float w, float h, float x, float y);
  bool talalat_vizsgalat(lovedek const& l);
  bool elo() { return !eltalalt; }
  float bal_oldal() { return x - w / 2; }
  float jobb_oldal() { return x + w / 2; }
  void set_x(float uj_x) { x = uj_x; }

 private:
  float w, h, x, y;
  bool eltalalt;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif  // URHAJO_H
