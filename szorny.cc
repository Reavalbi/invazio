#include "szorny.h"

szorny::szorny(float w, float h, float x, float y)
    : w(w), h{h}, x{x}, y{y}, eltalalt{false} {}

bool szorny::talalat_vizsgalat(lovedek const& l) {
  bool eredmeny = false;
  for (int oszlop = 0; oszlop < 2; ++oszlop) {
    for (int sor = 0; sor < 2; ++sor) {
      if (eltalalt[sor][oszlop]) {
        continue;
      }
      float lkx = l.x + l.r;
      float lky = l.y + l.r;
      float vr = l.r / 2;
      float x1 = x + oszlop * w / 2;
      float x2 = x1 + w / 2;
      float y1 = y + sor * h / 2;
      float y2 = y1 + h / 2;
      if (lky < y2 + vr && lky > y1 - vr && lkx < x2 + vr && lkx > x1 - vr) {
        eredmeny = true;
        eltalalt[sor][oszlop] = true;
      }
    }
  }
  return eredmeny;
}

bool szorny::elo() {
  for (int oszlop = 0; oszlop < 2; ++oszlop) {
    for (int sor = 0; sor < 2; ++sor) {
      if (!eltalalt[sor][oszlop]) {
        return true;
      }
    }
  }
  return false;
}

bool szorny::teljes() {
  for (int oszlop = 0; oszlop < 2; ++oszlop) {
    for (int sor = 0; sor < 2; ++sor) {
      if (eltalalt[sor][oszlop]) {
        return false;
      }
    }
  }
  return true;
}

void szorny::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (int oszlop = 0; oszlop < 2; ++oszlop) {
    for (int sor = 0; sor < 2; ++sor) {
      if (eltalalt[sor][oszlop]) {
        continue;
      }
      sf::RectangleShape rectangle;
      rectangle.setSize(sf::Vector2f(w / 2, h / 2));
      rectangle.setOutlineColor(sf::Color::Red);
      rectangle.setOutlineThickness(0);
      rectangle.setPosition(x + oszlop * w / 2, y + sor * h / 2);
      target.draw(rectangle);
    }
  }
}
