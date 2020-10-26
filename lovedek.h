#ifndef LOVEDEK_H
#define LOVEDEK_H

#include <SFML/Graphics.hpp>

class lovedek : public sf::Drawable {
 public:
  int r;
  float x, y;
  float x_sebesseg = 0.0f;

  lovedek(int r, float x, float y);
  void mozdit(float dy, float dx = 0.0f);
  bool talalat_vizsgalat(lovedek const& l);

 private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif  // LOVEDEK_H