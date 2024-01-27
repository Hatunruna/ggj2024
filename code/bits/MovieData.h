#ifndef MM_MOVIE_DATA_H
#define MM_MOVIE_DATA_H

#include <vector>
#include <string>

#include <gf/Random.h>
#include <gf/ResourceManager.h>

namespace mm {

  enum class MovieCountry {
    Canterlot,
    Gallifrey,
    Hyrule,
    Innistrad,
    Morrowind,
    Temeria,
    Valinor,
    Wonderland,
  };

  std::string toString(MovieCountry country);

  enum class MovieGenre {
    Action,
    Comedy,
    Drama,
    Fantasy,
    Horror,
    Musical,
    Romance,
    ScienceFiction,
    Western,
  };

  std::string toString(MovieGenre genre);

  enum class MovieTechnique {
    Animation,
    LiveAction,
    StopMotion,
  };

  std::string toString(MovieTechnique technique);

  enum class MovieRating {
    AllAges,
    Above12,
    Above16,
    Above18,
  };

  struct MovieData {
    std::string title;
    int year = 0;
    int duration = 0;
    int note = 0;
    MovieCountry country;
    MovieGenre genre;
    MovieTechnique technique;
    MovieRating rating;
    std::vector<std::string> themes;
    bool generated_by_ai = false;
  };

  std::vector<MovieData> loadDatabase(gf::ResourceManager& resources, gf::Random& random);

  enum class MovieConstraint {
    // title

    // year
    YearAfter1980,
    YearAfter1990,
    YearAfter2000,
    YearAfter2010,
    YearBefore1990,
    YearBefore2000,
    YearBefore2010,
    YearBefore2020,
    YearIsLeap,
    YearIsNotLeap,
    YearIsOdd,
    YearIsEven,
    // duration
    DurationMoreThan90,
    DurationMoreThan120,
    DurationMoreThan150,
    DurationLessThan120,
    DurationLessThan150,
    DurationLessThan180,
    // note
    NoteMoreThan2,
    NoteMoreThan3,
    NoteMoreThan4,
    NoteLessThan2,
    NoteLessThan3,
    NoteLessThan4,
    // country

    // genre
    // technique
    TechniqueIsAnimation,
    TechniqueIsLiveAction,
    TechniqueIsStopMotion,
    TechniqueIsNotAnimation,
    TechniqueIsNotLiveAction,
    TechniqueIsNotStopMotion,
    // rating
  };

  std::string toString(MovieConstraint constraint);

  std::vector<MovieConstraint> computeConstraints(std::size_t count, gf::Random& random);

  bool isMovieAcceptable(const MovieData& film, MovieConstraint constraint);

}

#endif // MM_MOVIE_DATA_H
