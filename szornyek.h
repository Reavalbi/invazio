#ifndef SZORNYEK_H
#define SZORNYEK_H

#include <SFML/Graphics.hpp>
#include <random>

#include "lovedek.h"
#include "szorny.h"

class szornyek : public sf::Drawable {
 public:
  szornyek(int sorok, int oszlopok, float x, float y, float szorny_magassag,
           float szorny_szelesseg, std::default_random_engine& rnd_engine);
  std::vector<lovedek> uj_lovedek();
  float jobb_oldal();
  float bal_oldal();
  void mozdit(float x, float y);
  bool talalat_vizsgalat(lovedek const& l);

 private:
  std::vector<std::vector<szorny>> sz;
  std::default_random_engine& rnd_engine;
  int sorok, oszlopok;
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif  // SZORNYEK_H
