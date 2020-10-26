#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <array>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "lovedek.h"
#include "szorny.h"
#include "szornyek.h"
#include "urhajo.h"

std::random_device rnd_dev;

// Choose a random mean between 1 and 6
std::default_random_engine rnd_engine(rnd_dev());

const float szorny_magassag = 30;
const float szorny_szelesseg = 55;


int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "szorny");
  szornyek sz{4, 11, 20, 40, szorny_magassag, szorny_szelesseg, rnd_engine};
  std::vector<lovedek> lovedekek, szorny_lovedekek;
  float urhajo_x = 400;
  sf::Clock loves_clock, frame_clock, szorny_loves_clock;
  int loves_kivaras = 250;
  float lovedek_sebesseg = 600.0 / (1.0 * 1000.0);
  float szorny_lovedek_sebesseg = 600.0 / (2.5 * 1000.0);
  float urhajo_sebesseg = 800.0 / (4.0 * 1000.0);
  float urhajo_mozgas = 0.0;
  bool lovunk = false;
  bool elso_loves = false;
  float szorny_sebesseg = 800.0 / (8.0 * 1000.0);
  urhajo uh{szorny_szelesseg, szorny_magassag, urhajo_x,
            600 - 5 - szorny_magassag};
  std::uniform_int_distribution<int> szlk_uniform_dist(500, 2000);
  int szlk = szlk_uniform_dist(rnd_engine);

  // check all the window's events that were triggered since the last
  // iteration of the loop
  sf::Event event;
  while (uh.elo()) {
    if (window.pollEvent(event)) {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed) {
        window.close();
        break;
      }
      if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
          case sf::Keyboard::Key::Space:
            lovunk = true;
            break;

          case sf::Keyboard::Key::Right:
            urhajo_mozgas = 1.0;
            break;

          case sf::Keyboard::Key::Left:
            urhajo_mozgas = -1.0;
            break;

          default:
            break;
        }
      }

      if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
          case sf::Keyboard::Key::Space:
            lovunk = false;
            elso_loves = true;
            break;
          case sf::Keyboard::Key::Right:
            urhajo_mozgas = 0.0;
            break;

          case sf::Keyboard::Key::Left:
            urhajo_mozgas = 0.0;
            break;

          default:
            break;
        }
      }
    }

    if (lovunk &&
        (loves_clock.getElapsedTime().asMilliseconds() > loves_kivaras ||
         elso_loves || lovedekek.size() == 0)) {
      lovedek l{5, urhajo_x - 2.5f, 590 - 5 - szorny_magassag};
      lovedekek.push_back(l);
      loves_clock.restart();
      elso_loves = false;
    }

    if (szorny_loves_clock.getElapsedTime().asMilliseconds() > szlk) {
      std::vector<lovedek> lk = sz.uj_lovedek();

      if (lk.size() > 0) {
        lk[0].x_sebesseg = szorny_sebesseg;
        std::cerr << szorny_sebesseg << std::endl;
        szorny_lovedekek.push_back(lk[0]);
      }
      szorny_loves_clock.restart();
      szlk = szlk_uniform_dist(rnd_engine);
    }

    sf::Time ft = frame_clock.restart();
    double lovedek_mozdulas =
        -1 * lovedek_sebesseg * ft.asMicroseconds() / 1000.0;
    for (int i = lovedekek.size() - 1; i >= 0; --i) {
      lovedekek[i].mozdit(lovedek_mozdulas);
      if (lovedekek[i].y < 0) {
        lovedekek.erase(lovedekek.begin() + i);
        continue;
      }
      if (sz.talalat_vizsgalat(lovedekek[i])) {
        lovedekek.erase(lovedekek.begin() + i);
        continue;
      }
    }

    float szorny_lovedek_mozdulas =
        szorny_lovedek_sebesseg * ft.asMicroseconds() / 1000.0;
    for (int i = szorny_lovedekek.size() - 1; i >= 0; --i) {
      float szlm_x =
          szorny_lovedekek[i].x_sebesseg * ft.asMicroseconds() / 1000.0;
      szorny_lovedekek[i].mozdit(szorny_lovedek_mozdulas, szlm_x);
      if (szorny_lovedekek[i].y > 600) {
        szorny_lovedekek.erase(szorny_lovedekek.begin() + i);
        continue;
      }
      for (int li = 0; li < lovedekek.size(); ++li) {
        if (lovedekek[li].talalat_vizsgalat(szorny_lovedekek[i])) {
          lovedekek.erase(lovedekek.begin() + li);
          szorny_lovedekek.erase(szorny_lovedekek.begin() + i);
          continue;
        }
      }
      if (uh.talalat_vizsgalat(szorny_lovedekek[i])) {
        szorny_lovedekek.erase(szorny_lovedekek.begin() + i);
        continue;
      }
    }

    double szorny_mozdulas = szorny_sebesseg * ft.asMicroseconds() / 1000.0;
    sz.mozdit(szorny_mozdulas, 0);

    if (sz.jobb_oldal() > 800) {
      szorny_sebesseg *= -1;
      sz.mozdit(800 - sz.jobb_oldal(), 10);
    }

    if (sz.bal_oldal() < 0) {
      szorny_sebesseg *= -1;
      sz.mozdit(0 - sz.bal_oldal(), 10);
    }

    urhajo_x += urhajo_mozgas * urhajo_sebesseg * ft.asMicroseconds() / 1000.0;
    uh.set_x(urhajo_x);

    window.clear(sf::Color::Blue);
    window.draw(sz);
    for (int i = 0; i < lovedekek.size(); ++i) {
      window.draw(lovedekek[i]);
    }
    for (int i = 0; i < szorny_lovedekek.size(); ++i) {
      window.draw(szorny_lovedekek[i]);
    }
    window.draw(uh);
    window.display();
  }

  while (true) {
    if (window.waitEvent(event)) {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed) {
        window.close();
        break;
      }
    }
  }

  return 0;
}