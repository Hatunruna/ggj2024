#include <algorithm>
#include <map>
#include <utility>
#include <iostream>

#include <gf/ResourceManager.h>

#include "bits/MovieData.h"

#include "config.h"

int main() {
  gf::ResourceManager resources;
  resources.addSearchDir(GAME_DATADIR);

  gf::Random random;

  auto db = mm::loadDatabase(resources, random);

  auto level = mm::computeLevel(db, 4, 20, random);

  std::cout << "Constraints:\n";

  for (auto constraint : level.constraints) {
    std::cout << '\t' << mm::toString(constraint) << '\n';
  }

  std::cout << "Movies:\n";

  for (const auto& movie : level.movies) {
    std::cout << '\t' << movie.title << " -> " << (mm::isMovieAcceptable(movie, level.constraints) ? "OK" : "KO") << '\n';
  }

}
