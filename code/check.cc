#include <algorithm>
#include <map>
#include <utility>
#include <iostream>

#include <gf/ResourceManager.h>

#include "bits/FilmData.h"

#include "config.h"

int main() {
  gf::ResourceManager resources;
  resources.addSearchDir(GAME_DATADIR);

  gf::Random random;

  auto db = mm::load_database(resources, random);

  std::map<std::pair<mm::FilmCountry, mm::FilmGenre>, int> counts;
  std::size_t maxSize = 0;

  for (auto& film : db) {
    counts[std::make_pair(film.country, film.genre)]++;
    maxSize = std::max(maxSize, film.title.size());
  }

  for (auto [ pair, count ] : counts) {
    std::cout << "Pair: " << static_cast<int>(pair.first) << ',' << static_cast<int>(pair.second) << ": " << count;

    if (count > 1) {
      std::cout << " <-";
    }

    std::cout << '\n';
  }

  std::cout << "Total: " << db.size() << '\n';
  std::cout << "Max size: " << maxSize << '\n';

}
