#include "szornyek.h"

szornyek::szornyek(int sorok, int oszlopok, float x, float y, float szorny_magassag,
         float szorny_szelesseg, std::default_random_engine& rnd_engine)
    : sorok{sorok}, oszlopok{oszlopok}, rnd_engine{rnd_engine} {
  for (int sor = 0; sor < sorok; ++sor) {
    std::vector<szorny> uj_sor;
    float uj_y = y + sor * (szorny_magassag + 10);
    for (int oszlop = 0; oszlop < oszlopok; ++oszlop) {
      float uj_x = x + oszlop * (szorny_szelesseg + 10);
      szorny uj_sz{szorny_szelesseg, szorny_magassag, uj_x, uj_y};
      uj_sor.push_back(uj_sz);
    }
    sz.push_back(uj_sor);
  }
}

std::vector<lovedek> szornyek::uj_lovedek() {
  std::vector<szorny> alsok;

  for (int oszlop = 0; oszlop < oszlopok; ++oszlop) {
    for (int sor = sorok - 1; sor >= 0; --sor) {
      if (sz[sor][oszlop].teljes()) {
        alsok.push_back(sz[sor][oszlop]);
        break;
      }
      if (sz[sor][oszlop].elo()) {
        break;
      }
    }
  }

  std::vector<lovedek> result;
  if (alsok.size() == 0) {
    return result;
  }
  std::uniform_int_distribution<int> uniform_dist(0, alsok.size() - 1);
  int lovo = uniform_dist(rnd_engine);
  szorny& lovo_szorny = alsok[lovo];
  lovedek l{3, lovo_szorny.x_kozep() - 1.5f, lovo_szorny.alja()};
  result.push_back(l);
  return result;
}

float szornyek::jobb_oldal() {
  float jo = 0;
  bool elso = true;
  for (int sor = 0; sor < sz.size(); ++sor) {
    for (int oszlop = 0; oszlop < sz[sor].size(); ++oszlop) {
      if (!sz[sor][oszlop].elo()) {
        continue;
      }
      float szjo = sz[sor][oszlop].jobb_oldal();
      if (elso || szjo > jo) {
        jo = szjo;
        elso = false;
      }
    }
  }
  return jo;
}

float szornyek::bal_oldal() {
  float bo = 0;
  bool elso = true;
  for (int sor = 0; sor < sz.size(); ++sor) {
    for (int oszlop = 0; oszlop < sz[sor].size(); ++oszlop) {
      if (!sz[sor][oszlop].elo()) {
        continue;
      }
      float szbo = sz[sor][oszlop].bal_oldal();
      if (elso || szbo < bo) {
        bo = szbo;
        elso = false;
      }
    }
  }
  return bo;
}

void szornyek::mozdit(float x, float y) {
  for (int sor = 0; sor < sz.size(); ++sor) {
    for (int oszlop = 0; oszlop < sz[sor].size(); ++oszlop) {
      sz[sor][oszlop].mozdit(x, y);
    }
  }
}

bool szornyek::talalat_vizsgalat(lovedek const& l) {
  bool eredmeny = false;
  for (int sor = 0; sor < sz.size(); ++sor) {
    for (int oszlop = 0; oszlop < sz[sor].size(); ++oszlop) {
      if (sz[sor][oszlop].talalat_vizsgalat(l)) {
        eredmeny = true;
      }
    }
  }
  return eredmeny;
}

void szornyek::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (int sor = 0; sor < sz.size(); ++sor) {
    for (int oszlop = 0; oszlop < sz[sor].size(); ++oszlop) {
      target.draw(sz[sor][oszlop]);
    }
  }
}
