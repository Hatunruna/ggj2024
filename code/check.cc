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
    mm::MovieConstraint::CountryIsCanterlot,
    mm::MovieConstraint::CountryIsGallifrey,
    mm::MovieConstraint::CountryIsHyrule,
    mm::MovieConstraint::CountryIsInnistrad,
    mm::MovieConstraint::CountryIsMorrowind,
    mm::MovieConstraint::CountryIsTemeria,
    mm::MovieConstraint::CountryIsValinor,
    mm::MovieConstraint::CountryIsWonderland,
    mm::MovieConstraint::CountryIsNotCanterlot,
    mm::MovieConstraint::CountryIsNotGallifrey,
    mm::MovieConstraint::CountryIsNotHyrule,
    mm::MovieConstraint::CountryIsNotInnistrad,
    mm::MovieConstraint::CountryIsNotMorrowind,
    mm::MovieConstraint::CountryIsNotTemeria,
    mm::MovieConstraint::CountryIsNotValinor,
    mm::MovieConstraint::CountryIsNotWonderland,
    // genre
    mm::MovieConstraint::GenreIsAction,
    mm::MovieConstraint::GenreIsComedy,
    mm::MovieConstraint::GenreIsDrama,
    mm::MovieConstraint::GenreIsFantasy,
    mm::MovieConstraint::GenreIsHorror,
    mm::MovieConstraint::GenreIsMusical,
    mm::MovieConstraint::GenreIsRomance,
    mm::MovieConstraint::GenreIsScienceFiction,
    mm::MovieConstraint::GenreIsWestern,
    mm::MovieConstraint::GenreIsNotAction,
    mm::MovieConstraint::GenreIsNotComedy,
    mm::MovieConstraint::GenreIsNotDrama,
    mm::MovieConstraint::GenreIsNotFantasy,
    mm::MovieConstraint::GenreIsNotHorror,
    mm::MovieConstraint::GenreIsNotMusical,
    mm::MovieConstraint::GenreIsNotRomance,
    mm::MovieConstraint::GenreIsNotScienceFiction,
    mm::MovieConstraint::GenreIsNotWestern,
    // technique
    mm::MovieConstraint::TechniqueIsAnimation,
    mm::MovieConstraint::TechniqueIsLiveAction,
    mm::MovieConstraint::TechniqueIsStopMotion,
    mm::MovieConstraint::TechniqueIsNotAnimation,
    mm::MovieConstraint::TechniqueIsNotLiveAction,
    mm::MovieConstraint::TechniqueIsNotStopMotion,
    // rating
    mm::MovieConstraint::RatingChildOf10,
    mm::MovieConstraint::RatingTeenagerOf14,
    mm::MovieConstraint::RatingTeenagerOf17,
    mm::MovieConstraint::RatingMoreThan0,
    mm::MovieConstraint::RatingMoreThan12,
    mm::MovieConstraint::RatingMoreThan16,
    mm::MovieConstraint::RatingMoreThan18,
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
