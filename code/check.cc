#include <map>
#include <utility>
#include <iostream>


#include <gf/ResourceManager.h>

#include "bits/FilmData.h"

#include "config.h"

int main() {
  gf::ResourceManager resources;
  resources.addSearchDir(GAME_DATADIR);
  auto db = mm::load_database(resources);

  std::map<std::pair<mm::FilmCountry, mm::FilmGenre>, int> counts;

  for (auto& film : db) {
    counts[std::make_pair(film.country, film.genre)]++;
  }

  for (auto [ pair, count ] : counts) {
    std::cout << "Pair: " << static_cast<int>(pair.first) << ',' << static_cast<int>(pair.second) << ": " << count << '\n';
  }

  std::cout << "Total: " << db.size() << '\n';

}
