#include <algorithm>
#include <map>
#include <utility>
#include <iostream>

#include <gf/ResourceManager.h>

#include "bits/MovieData.h"

#include "config.h"

namespace {

  constexpr mm::MovieConstraint AllConstraints[] = {
    // title
    mm::MovieConstraint::TitleWithOddWords,
    mm::MovieConstraint::TitleWithEvenWords,
    mm::MovieConstraint::TitleWithLessThan16Letters,
    mm::MovieConstraint::TitleWithMoreThan16Letters,
    // year
    mm::MovieConstraint::YearAfter1980,
    mm::MovieConstraint::YearAfter1990,
    mm::MovieConstraint::YearAfter2000,
    mm::MovieConstraint::YearAfter2010,
    mm::MovieConstraint::YearBefore1990,
    mm::MovieConstraint::YearBefore2000,
    mm::MovieConstraint::YearBefore2010,
    mm::MovieConstraint::YearBefore2020,
    mm::MovieConstraint::YearIsLeap,
    mm::MovieConstraint::YearIsNotLeap,
    mm::MovieConstraint::YearIsOdd,
    mm::MovieConstraint::YearIsEven,
    // duration
    mm::MovieConstraint::DurationMoreThan90,
    mm::MovieConstraint::DurationMoreThan120,
    mm::MovieConstraint::DurationMoreThan150,
    mm::MovieConstraint::DurationLessThan120,
    mm::MovieConstraint::DurationLessThan150,
    mm::MovieConstraint::DurationLessThan180,
    // note
    mm::MovieConstraint::NoteMoreThan2,
    mm::MovieConstraint::NoteMoreThan3,
    mm::MovieConstraint::NoteMoreThan4,
    mm::MovieConstraint::NoteLessThan2,
    mm::MovieConstraint::NoteLessThan3,
    mm::MovieConstraint::NoteLessThan4,
    // country
    // genre
    // technique
    mm::MovieConstraint::TechniqueIsAnimation,
    mm::MovieConstraint::TechniqueIsLiveAction,
    mm::MovieConstraint::TechniqueIsStopMotion,
    mm::MovieConstraint::TechniqueIsNotAnimation,
    mm::MovieConstraint::TechniqueIsNotLiveAction,
    mm::MovieConstraint::TechniqueIsNotStopMotion,
    // rating
  };

}

int main() {
  gf::ResourceManager resources;
  resources.addSearchDir(GAME_DATADIR);

  gf::Random random;

  auto db = mm::loadDatabase(resources, random);

  std::cout << "Total number of movies: " << db.size() << '\n';

  std::map<std::pair<mm::MovieCountry, mm::MovieGenre>, int> counts;
  std::size_t maxSize = 0;
  std::size_t avgSize = 0;

  for (auto& movie : db) {
    counts[std::make_pair(movie.country, movie.genre)]++;
    maxSize = std::max(maxSize, movie.title.size());
    avgSize += mm::numberOfLetters(movie.title);
  }

  std::cout << "Max title size: " << maxSize << '\n';
  std::cout << "Avg title size: " << avgSize / db.size() << '\n';

  for (auto [ pair, count ] : counts) {
    if (count > 1) {
      std::cout << '(' << mm::toString(pair.first) << ',' << mm::toString(pair.second) << ") has more than one occurrence\n";
    }
  }


  std::cout << "------\n";

  for (auto constraint : AllConstraints) {
    std::size_t count = 0;

    for (auto& movie : db) {
      if (isMovieAcceptable(movie, constraint)) {
        ++count;
      }
    }

    std::cout << "Constraint '" << mm::toString(constraint) << "' is fullfilled by " << count << '/' << db.size() << " movies\n";
  }

  std::cout << "------\n";

  for (auto& movie : db) {
    std::size_t count = 0;

    for (auto constraint : AllConstraints) {
      if (isMovieAcceptable(movie, constraint)) {
        ++count;
      }
    }

    std::cout << "Movie '" << movie.title << "' fullfills " << count << '/' << std::size(AllConstraints) << " constraints\n";
  }


}
