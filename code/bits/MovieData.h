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
    bool generated_by_ai = false;
  };

  std::string getTexturePath(const std::string& title);

  std::vector<MovieData> loadDatabase(gf::ResourceManager& resources, gf::Random& random);

  std::size_t numberOfLetters(const std::string& text);
  std::size_t numberOfWords(const std::string& text);

  enum class MovieConstraint {
    // title
    TitleWithOddWords,
    TitleWithEvenWords,
    TitleWithLessThan16Letters,
    TitleWithMoreThan16Letters,
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
    CountryIsCanterlot,
    CountryIsGallifrey,
    CountryIsHyrule,
    CountryIsInnistrad,
    CountryIsMorrowind,
    CountryIsTemeria,
    CountryIsValinor,
    CountryIsWonderland,
    CountryIsNotCanterlot,
    CountryIsNotGallifrey,
    CountryIsNotHyrule,
    CountryIsNotInnistrad,
    CountryIsNotMorrowind,
    CountryIsNotTemeria,
    CountryIsNotValinor,
    CountryIsNotWonderland,
    // genre
    GenreIsAction,
    GenreIsComedy,
    GenreIsDrama,
    GenreIsFantasy,
    GenreIsHorror,
    GenreIsMusical,
    GenreIsRomance,
    GenreIsScienceFiction,
    GenreIsWestern,
    GenreIsNotAction,
    GenreIsNotComedy,
    GenreIsNotDrama,
    GenreIsNotFantasy,
    GenreIsNotHorror,
    GenreIsNotMusical,
    GenreIsNotRomance,
    GenreIsNotScienceFiction,
    GenreIsNotWestern,
    // technique
    TechniqueIsAnimation,
    TechniqueIsLiveAction,
    TechniqueIsStopMotion,
    TechniqueIsNotAnimation,
    TechniqueIsNotLiveAction,
    TechniqueIsNotStopMotion,
    // rating
    RatingLessThan12,
    RatingLessThan16,
    RatingLessThan18,
    RatingMoreThan12,
    RatingMoreThan16,
    RatingMoreThan18,
  };

  std::string toString(MovieConstraint constraint);
  bool isMovieAcceptable(const MovieData& movie, MovieConstraint constraint);
  bool isMovieAcceptable(const MovieData& movie, const std::vector<MovieConstraint>& constraints);
  std::vector<MovieConstraint> whyMovieNotAccepted(const MovieData& movie, const std::vector<MovieConstraint>& constraints);

  struct MovieLevel {
    std::vector<MovieConstraint> constraints;
    std::vector<MovieData> movies;
  };

  MovieLevel computeLevel(const std::vector<MovieData>& database, std::size_t contraintCount, std::size_t movieCount, gf::Random& random);


}

#endif // MM_MOVIE_DATA_H
