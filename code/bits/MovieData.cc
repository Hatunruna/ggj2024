#include "MovieData.h"

#include <cassert>
#include <fstream>

#include <nlohmann/json.hpp>

namespace mm {

  std::string toString(MovieCountry country) {
    switch (country) {
      case MovieCountry::Canterlot:
        return "Canterlot";
      case MovieCountry::Gallifrey:
        return "Gallifrey";
      case MovieCountry::Hyrule:
        return "Hyrule";
      case MovieCountry::Innistrad:
        return "Innistrad";
      case MovieCountry::Morrowind:
        return "Morrowind";
      case MovieCountry::Temeria:
        return "Temeria";
      case MovieCountry::Valinor:
        return "Valinor";
      case MovieCountry::Wonderland:
        return "Wonderland";
    }

    assert(false);
    return "??";
  }

  std::string toString(MovieGenre genre) {
    switch (genre) {
      case MovieGenre::Action:
        return "Action";
      case MovieGenre::Comedy:
        return "Comedy";
      case MovieGenre::Drama:
        return "Drama";
      case MovieGenre::Fantasy:
        return "Fantasy";
      case MovieGenre::Horror:
        return "Horror";
      case MovieGenre::Musical:
        return "Musical";
      case MovieGenre::Romance:
        return "Romance";
      case MovieGenre::ScienceFiction:
        return "Science Fiction";
      case MovieGenre::Western:
        return "Western";
    }

    assert(false);
    return "??";
  }

  std::string toString(MovieTechnique technique) {
    switch (technique) {
      case MovieTechnique::Animation:
        return "Animated";
      case MovieTechnique::LiveAction:
        return "Live Action";
      case MovieTechnique::StopMotion:
        return "Stop Motion";
    }

    assert(false);
    return "??";
  }

  NLOHMANN_JSON_SERIALIZE_ENUM(MovieCountry, {
    { MovieCountry::Canterlot, "Canterlot" },
    { MovieCountry::Gallifrey, "Gallifrey" },
    { MovieCountry::Hyrule, "Hyrule" },
    { MovieCountry::Innistrad, "Innistrad" },
    { MovieCountry::Morrowind, "Morrowind" },
    { MovieCountry::Temeria, "Temeria" },
    { MovieCountry::Valinor, "Valinor" },
    { MovieCountry::Wonderland, "Wonderland" },
  })

  NLOHMANN_JSON_SERIALIZE_ENUM(MovieGenre, {
    { MovieGenre::Action, "Action" },
    { MovieGenre::Comedy, "Comedy" },
    { MovieGenre::Drama, "Drama" },
    { MovieGenre::Fantasy, "Fantasy" },
    { MovieGenre::Horror, "Horror" },
    { MovieGenre::Musical, "Musical" },
    { MovieGenre::Romance, "Romance" },
    { MovieGenre::ScienceFiction, "ScienceFiction" },
    { MovieGenre::Western, "Western" },
  })

  NLOHMANN_JSON_SERIALIZE_ENUM(MovieTechnique, {
    { MovieTechnique::Animation, "Animated" },
    { MovieTechnique::LiveAction, "LiveAction" },
    { MovieTechnique::StopMotion, "StopMotion" },
  })

  NLOHMANN_JSON_SERIALIZE_ENUM(MovieRating, {
    { MovieRating::AllAges, "0+" },
    { MovieRating::Above12, "12+" },
    { MovieRating::Above16, "16+" },
    { MovieRating::Above18, "18+" },
  })

  void from_json(const nlohmann::json& j, MovieData& data) {
    j.at("title").get_to(data.title);
    j.at("country").get_to(data.country);
    j.at("genre").get_to(data.genre);
    j.at("rating").get_to(data.rating);
  }

  std::string getTexturePath(const std::string& title) {
    std::string texturePath = "images/posters/";

    std::string titleEscaped = title;
    for (std::size_t i = 0; i < title.size(); ++i) {
      if (titleEscaped[i] == ' ') {
        titleEscaped.replace(i, 1, "_");
      }
    }
    texturePath += titleEscaped + ".png";

    return texturePath;
  }

  std::vector<MovieData> loadDatabase(gf::ResourceManager& resources, gf::Random& random) {
    std::vector<MovieData> db;

    auto filename = resources.getAbsolutePath("database.json");
    std::ifstream ifs(filename);
    nlohmann::json::parse(ifs).get_to(db);

    constexpr MovieTechnique Techniques[] { MovieTechnique::Animation, MovieTechnique::LiveAction, MovieTechnique::StopMotion };
    std::discrete_distribution<std::size_t> techniqueDistribution({ 0.3, 0.65, 0.05 });

    for (auto& film : db) {
      film.year = random.computeUniformInteger(1970, 2024);
      film.duration = random.computeUniformInteger(60, 200);
      film.note = random.computeUniformInteger(1, 5);
      film.technique = Techniques[techniqueDistribution(random.getEngine())];
      film.generated_by_ai = random.computeBernoulli(0.25);
    }

    return db;
  }

  std::size_t numberOfLetters(const std::string& text) {
    return std::count_if(text.begin(), text.end(), [](char c) { return c != ' '; });
  }

  std::size_t numberOfWords(const std::string& text) {
    return 1 + std::count_if(text.begin(), text.end(), [](char c) { return c == ' '; });
  }

  std::string toString(MovieConstraint constraint) {
    switch (constraint) {
      // title
      case MovieConstraint::TitleWithOddWords:
        return "The title has a odd number of words";
      case MovieConstraint::TitleWithEvenWords:
        return "The title has an even number of words";
      case MovieConstraint::TitleWithLessThan16Letters:
        return "The title has 16 letters or less";
      case MovieConstraint::TitleWithMoreThan16Letters:
        return "The title has 16 letters or more";
      // year
      case MovieConstraint::YearAfter1980:
        return "The movie was released in 1980 or after";
      case MovieConstraint::YearAfter1990:
        return "The movie was released in 1990 or after";
      case MovieConstraint::YearAfter2000:
        return "The movie was released in 2000 or after";
      case MovieConstraint::YearAfter2010:
        return "The movie was released in 2010 or after";
      case MovieConstraint::YearBefore1990:
        return "The movie was released in 1990 or before";
      case MovieConstraint::YearBefore2000:
        return "The movie was released in 2000 or before";
      case MovieConstraint::YearBefore2010:
        return "The movie was released in 2010 or before";
      case MovieConstraint::YearBefore2020:
        return "The movie was released in 2020 or before";
      case MovieConstraint::YearIsLeap:
        return "The movie was released in a leap year";
      case MovieConstraint::YearIsNotLeap:
        return "The movie was released in a non-leap year";
      case MovieConstraint::YearIsOdd:
        return "The movie was released in a odd year";
      case MovieConstraint::YearIsEven:
        return "The movie was released in an even year";
      // duration
      case MovieConstraint::DurationMoreThan90:
        return "The movie lasts 90 minutes or more";
      case MovieConstraint::DurationMoreThan120:
        return "The movie lasts 120 minutes or more";
      case MovieConstraint::DurationMoreThan150:
        return "The movie lasts 150 minutes or more";
      case MovieConstraint::DurationLessThan120:
        return "The movie lasts 120 minutes or less";
      case MovieConstraint::DurationLessThan150:
        return "The movie lasts 150 minutes or less";
      case MovieConstraint::DurationLessThan180:
        return "The movie lasts 180 minutes or less";
      // note
      case MovieConstraint::NoteMoreThan2:
        return "The movie has 2 stars or more";
      case MovieConstraint::NoteMoreThan3:
        return "The movie has 3 stars or more";
      case MovieConstraint::NoteMoreThan4:
        return "The movie has 4 stars or more";
      case MovieConstraint::NoteLessThan2:
        return "The movie has 2 stars or less";
      case MovieConstraint::NoteLessThan3:
        return "The movie has 3 stars or less";
      case MovieConstraint::NoteLessThan4:
        return "The movie has 4 stars or less";
      // country
      case MovieConstraint::CountryIsCanterlot:
        return "The movie comes from Canterlot";
      case MovieConstraint::CountryIsGallifrey:
        return "The movie comes from Gallifrey";
      case MovieConstraint::CountryIsHyrule:
        return "The movie comes from Hyrule";
      case MovieConstraint::CountryIsInnistrad:
        return "The movie comes from Innistrad";
      case MovieConstraint::CountryIsMorrowind:
        return "The movie comes from Morrowind";
      case MovieConstraint::CountryIsTemeria:
        return "The movie comes from Temeria";
      case MovieConstraint::CountryIsValinor:
        return "The movie comes from Valinor";
      case MovieConstraint::CountryIsWonderland:
        return "The movie comes from Wonderland";
      case MovieConstraint::CountryIsNotCanterlot:
        return "The movie does not come from Canterlot";
      case MovieConstraint::CountryIsNotGallifrey:
        return "The movie does not come from Gallifrey";
      case MovieConstraint::CountryIsNotHyrule:
        return "The movie does not come from Hyrule";
      case MovieConstraint::CountryIsNotInnistrad:
        return "The movie does not come from Innistrad";
      case MovieConstraint::CountryIsNotMorrowind:
        return "The movie does not come from Morrowind";
      case MovieConstraint::CountryIsNotTemeria:
        return "The movie does not come from Temeria";
      case MovieConstraint::CountryIsNotValinor:
        return "The movie does not come from Valinor";
      case MovieConstraint::CountryIsNotWonderland:
        return "The movie does not come from Wonderland";
      // genre
      case MovieConstraint::GenreIsAction:
        return "The movie is an action movie";
      case MovieConstraint::GenreIsComedy:
        return "The movie is a comedy";
      case MovieConstraint::GenreIsDrama:
        return "The movie is a drama";
      case MovieConstraint::GenreIsFantasy:
        return "The movie is a fantasy movie";
      case MovieConstraint::GenreIsHorror:
        return "The movie is a horror movie";
      case MovieConstraint::GenreIsMusical:
        return "The movie is a musical movie";
      case MovieConstraint::GenreIsRomance:
        return "The movie is a romance";
      case MovieConstraint::GenreIsScienceFiction:
        return "The movie is a sci-fi movie";
      case MovieConstraint::GenreIsWestern:
        return "The movie is a western";
      case MovieConstraint::GenreIsNotAction:
        return "The movie is not an action movie";
      case MovieConstraint::GenreIsNotComedy:
        return "The movie is not a comedy";
      case MovieConstraint::GenreIsNotDrama:
        return "The movie is not a drama";
      case MovieConstraint::GenreIsNotFantasy:
        return "The movie is not a fantasy movie";
      case MovieConstraint::GenreIsNotHorror:
        return "The movie is not a horror movie";
      case MovieConstraint::GenreIsNotMusical:
        return "The movie is not a musical movie";
      case MovieConstraint::GenreIsNotRomance:
        return "The movie is not a romance";
      case MovieConstraint::GenreIsNotScienceFiction:
        return "The movie is not a sci-fi movie";
      case MovieConstraint::GenreIsNotWestern:
        return "The movie is not a western";
      // technique
      case MovieConstraint::TechniqueIsAnimation:
        return "The movie is in animation";
      case MovieConstraint::TechniqueIsLiveAction:
        return "The movie is in live action";
      case MovieConstraint::TechniqueIsStopMotion:
        return "The movie is in stop motion";
      case MovieConstraint::TechniqueIsNotAnimation:
        return "The movie is not in animation";
      case MovieConstraint::TechniqueIsNotLiveAction:
        return "The movie is not in live action";
      case MovieConstraint::TechniqueIsNotStopMotion:
        return "The movie is not in stop motion";
      // rating
      case MovieConstraint::RatingLessThan12:
        return "The movie is authorized for 0-11";
      case MovieConstraint::RatingLessThan16:
        return "The movie is authorized for 0-15";
      case MovieConstraint::RatingLessThan18:
        return "The movie is authorized for 0-17";
      case MovieConstraint::RatingMoreThan12:
        return "The movie is only authorized for 12+";
      case MovieConstraint::RatingMoreThan16:
        return "The movie is only authorized for 16+";
      case MovieConstraint::RatingMoreThan18:
        return "The movie is only authorized for 18+";
    }

    assert(false);
    return "??";
  }

  constexpr bool isLeap(int year) {
    return (year % 100 == 0) ? (year % 400 == 0) : (year % 4 == 0);
  }

  bool isMovieAcceptable(const MovieData& movie, MovieConstraint constraint) {
    switch (constraint) {
      // title
      case MovieConstraint::TitleWithOddWords:
        return numberOfWords(movie.title) % 2 != 0;
      case MovieConstraint::TitleWithEvenWords:
        return numberOfWords(movie.title) % 2 == 0;
      case MovieConstraint::TitleWithLessThan16Letters:
        return numberOfLetters(movie.title) >= 16;
      case MovieConstraint::TitleWithMoreThan16Letters:
        return numberOfLetters(movie.title) <= 16;
      // year
      case MovieConstraint::YearAfter1980:
        return movie.year >= 1980;
      case MovieConstraint::YearAfter1990:
        return movie.year >= 1990;
      case MovieConstraint::YearAfter2000:
        return movie.year >= 2000;
      case MovieConstraint::YearAfter2010:
        return movie.year >= 2010;
      case MovieConstraint::YearBefore1990:
        return movie.year <= 1990;
      case MovieConstraint::YearBefore2000:
        return movie.year <= 2000;
      case MovieConstraint::YearBefore2010:
        return movie.year <= 2010;
      case MovieConstraint::YearBefore2020:
        return movie.year <= 2020;
      case MovieConstraint::YearIsLeap:
        return isLeap(movie.year);
      case MovieConstraint::YearIsNotLeap:
        return !isLeap(movie.year);
      case MovieConstraint::YearIsOdd:
        return movie.year % 2 != 0;
      case MovieConstraint::YearIsEven:
        return movie.year % 2 == 0;
      // duration
      case MovieConstraint::DurationMoreThan90:
        return movie.duration >= 90;
      case MovieConstraint::DurationMoreThan120:
        return movie.duration >= 120;
      case MovieConstraint::DurationMoreThan150:
        return movie.duration >= 150;
      case MovieConstraint::DurationLessThan120:
        return movie.duration <= 120;
      case MovieConstraint::DurationLessThan150:
        return movie.duration <= 150;
      case MovieConstraint::DurationLessThan180:
        return movie.duration <= 180;
      // note
      case MovieConstraint::NoteMoreThan2:
        return movie.note >= 2;
      case MovieConstraint::NoteMoreThan3:
        return movie.note >= 3;
      case MovieConstraint::NoteMoreThan4:
        return movie.note >= 4;
      case MovieConstraint::NoteLessThan2:
        return movie.note <= 2;
      case MovieConstraint::NoteLessThan3:
        return movie.note <= 3;
      case MovieConstraint::NoteLessThan4:
        return movie.note <= 4;
      // country
      case MovieConstraint::CountryIsCanterlot:
        return movie.country == MovieCountry::Canterlot;
      case MovieConstraint::CountryIsGallifrey:
        return movie.country == MovieCountry::Gallifrey;
      case MovieConstraint::CountryIsHyrule:
        return movie.country == MovieCountry::Hyrule;
      case MovieConstraint::CountryIsInnistrad:
        return movie.country == MovieCountry::Innistrad;
      case MovieConstraint::CountryIsMorrowind:
        return movie.country == MovieCountry::Morrowind;
      case MovieConstraint::CountryIsTemeria:
        return movie.country == MovieCountry::Temeria;
      case MovieConstraint::CountryIsValinor:
        return movie.country == MovieCountry::Valinor;
      case MovieConstraint::CountryIsWonderland:
        return movie.country == MovieCountry::Wonderland;
      case MovieConstraint::CountryIsNotCanterlot:
        return movie.country != MovieCountry::Canterlot;
      case MovieConstraint::CountryIsNotGallifrey:
        return movie.country != MovieCountry::Gallifrey;
      case MovieConstraint::CountryIsNotHyrule:
        return movie.country != MovieCountry::Hyrule;
      case MovieConstraint::CountryIsNotInnistrad:
        return movie.country != MovieCountry::Innistrad;
      case MovieConstraint::CountryIsNotMorrowind:
        return movie.country != MovieCountry::Morrowind;
      case MovieConstraint::CountryIsNotTemeria:
        return movie.country != MovieCountry::Temeria;
      case MovieConstraint::CountryIsNotValinor:
        return movie.country != MovieCountry::Valinor;
      case MovieConstraint::CountryIsNotWonderland:
        return movie.country != MovieCountry::Wonderland;
      // genre
      case MovieConstraint::GenreIsAction:
        return movie.genre == MovieGenre::Action;
      case MovieConstraint::GenreIsComedy:
        return movie.genre == MovieGenre::Comedy;
      case MovieConstraint::GenreIsDrama:
        return movie.genre == MovieGenre::Drama;
      case MovieConstraint::GenreIsFantasy:
        return movie.genre == MovieGenre::Fantasy;
      case MovieConstraint::GenreIsHorror:
        return movie.genre == MovieGenre::Horror;
      case MovieConstraint::GenreIsMusical:
        return movie.genre == MovieGenre::Musical;
      case MovieConstraint::GenreIsRomance:
        return movie.genre == MovieGenre::Romance;
      case MovieConstraint::GenreIsScienceFiction:
        return movie.genre == MovieGenre::ScienceFiction;
      case MovieConstraint::GenreIsWestern:
        return movie.genre == MovieGenre::Western;
      case MovieConstraint::GenreIsNotAction:
        return movie.genre != MovieGenre::Action;
      case MovieConstraint::GenreIsNotComedy:
        return movie.genre != MovieGenre::Comedy;
      case MovieConstraint::GenreIsNotDrama:
        return movie.genre != MovieGenre::Drama;
      case MovieConstraint::GenreIsNotFantasy:
        return movie.genre != MovieGenre::Fantasy;
      case MovieConstraint::GenreIsNotHorror:
        return movie.genre != MovieGenre::Horror;
      case MovieConstraint::GenreIsNotMusical:
        return movie.genre != MovieGenre::Musical;
      case MovieConstraint::GenreIsNotRomance:
        return movie.genre != MovieGenre::Romance;
      case MovieConstraint::GenreIsNotScienceFiction:
        return movie.genre != MovieGenre::ScienceFiction;
      case MovieConstraint::GenreIsNotWestern:
        return movie.genre != MovieGenre::Western;
      // technique
      case MovieConstraint::TechniqueIsAnimation:
        return movie.technique == MovieTechnique::Animation;
      case MovieConstraint::TechniqueIsLiveAction:
        return movie.technique == MovieTechnique::LiveAction;
      case MovieConstraint::TechniqueIsStopMotion:
        return movie.technique == MovieTechnique::StopMotion;
      case MovieConstraint::TechniqueIsNotAnimation:
        return movie.technique != MovieTechnique::Animation;
      case MovieConstraint::TechniqueIsNotLiveAction:
        return movie.technique != MovieTechnique::LiveAction;
      case MovieConstraint::TechniqueIsNotStopMotion:
        return movie.technique != MovieTechnique::StopMotion;
      // rating
      case MovieConstraint::RatingLessThan12:
        return movie.rating < MovieRating::Above12;
      case MovieConstraint::RatingLessThan16:
        return movie.rating < MovieRating::Above16;
      case MovieConstraint::RatingLessThan18:
        return movie.rating < MovieRating::Above18;
      case MovieConstraint::RatingMoreThan12:
        return movie.rating >= MovieRating::Above12;
      case MovieConstraint::RatingMoreThan16:
        return movie.rating >= MovieRating::Above16;
      case MovieConstraint::RatingMoreThan18:
        return movie.rating >= MovieRating::Above18;
    }

    return true;
  }

  bool isMovieAcceptable(const MovieData& movie, const std::vector<MovieConstraint>& constraints) {
    return std::all_of(constraints.begin(), constraints.end(), [&](MovieConstraint constraint) {
      return isMovieAcceptable(movie, constraint);
    });
  }

  std::vector<MovieConstraint> whyMovieNotAccepted(const MovieData& movie, const std::vector<MovieConstraint>& constraints) {
    std::vector<MovieConstraint> notAccepted;

    for (auto constraint : constraints) {
      if (!isMovieAcceptable(movie, constraint)) {
        notAccepted.push_back(constraint);
      }
    }

    assert(!notAccepted.empty());
    return notAccepted;
  }

  MovieLevel computeLevel(const std::vector<MovieData>& database, std::size_t constraintCount, std::size_t movieCount, gf::Random& random) {
    const std::vector<MovieConstraint> constraintsByType[] = {
      {
        // title
        MovieConstraint::TitleWithOddWords,
        MovieConstraint::TitleWithEvenWords,
        MovieConstraint::TitleWithLessThan16Letters,
        MovieConstraint::TitleWithMoreThan16Letters,
      },
      {
        // year
        MovieConstraint::YearAfter1980,
        MovieConstraint::YearAfter1990,
        MovieConstraint::YearAfter2000,
        MovieConstraint::YearAfter2010,
        MovieConstraint::YearBefore1990,
        MovieConstraint::YearBefore2000,
        MovieConstraint::YearBefore2010,
        MovieConstraint::YearBefore2020,
        MovieConstraint::YearIsLeap,
        MovieConstraint::YearIsNotLeap,
        MovieConstraint::YearIsOdd,
        MovieConstraint::YearIsEven,
      },
      {
        // duration
        MovieConstraint::DurationMoreThan90,
        MovieConstraint::DurationMoreThan120,
        MovieConstraint::DurationMoreThan150,
        MovieConstraint::DurationLessThan120,
        MovieConstraint::DurationLessThan150,
        MovieConstraint::DurationLessThan180,
      },
      {
        // note
        MovieConstraint::NoteMoreThan2,
        MovieConstraint::NoteMoreThan3,
        MovieConstraint::NoteMoreThan4,
        MovieConstraint::NoteLessThan2,
        MovieConstraint::NoteLessThan3,
        MovieConstraint::NoteLessThan4,
      },
      {
        // country
        MovieConstraint::CountryIsCanterlot,
        MovieConstraint::CountryIsGallifrey,
        MovieConstraint::CountryIsHyrule,
        MovieConstraint::CountryIsInnistrad,
        MovieConstraint::CountryIsMorrowind,
        MovieConstraint::CountryIsTemeria,
        MovieConstraint::CountryIsValinor,
        MovieConstraint::CountryIsWonderland,
        MovieConstraint::CountryIsNotCanterlot,
        MovieConstraint::CountryIsNotGallifrey,
        MovieConstraint::CountryIsNotHyrule,
        MovieConstraint::CountryIsNotInnistrad,
        MovieConstraint::CountryIsNotMorrowind,
        MovieConstraint::CountryIsNotTemeria,
        MovieConstraint::CountryIsNotValinor,
        MovieConstraint::CountryIsNotWonderland,
      },
      {
        // genre
        MovieConstraint::GenreIsAction,
        MovieConstraint::GenreIsComedy,
        MovieConstraint::GenreIsDrama,
        MovieConstraint::GenreIsFantasy,
        MovieConstraint::GenreIsHorror,
        MovieConstraint::GenreIsMusical,
        MovieConstraint::GenreIsRomance,
        MovieConstraint::GenreIsScienceFiction,
        MovieConstraint::GenreIsWestern,
        MovieConstraint::GenreIsNotAction,
        MovieConstraint::GenreIsNotComedy,
        MovieConstraint::GenreIsNotDrama,
        MovieConstraint::GenreIsNotFantasy,
        MovieConstraint::GenreIsNotHorror,
        MovieConstraint::GenreIsNotMusical,
        MovieConstraint::GenreIsNotRomance,
        MovieConstraint::GenreIsNotScienceFiction,
        MovieConstraint::GenreIsNotWestern,
      },
      {
        // technique
        MovieConstraint::TechniqueIsAnimation,
        MovieConstraint::TechniqueIsLiveAction,
        MovieConstraint::TechniqueIsStopMotion,
        MovieConstraint::TechniqueIsNotAnimation,
        MovieConstraint::TechniqueIsNotLiveAction,
        MovieConstraint::TechniqueIsNotStopMotion,
      },
      {
        // rating
        MovieConstraint::RatingLessThan12,
        MovieConstraint::RatingLessThan16,
        MovieConstraint::RatingLessThan18,
        MovieConstraint::RatingMoreThan12,
        MovieConstraint::RatingMoreThan16,
        MovieConstraint::RatingMoreThan18,
      },
    };

    assert(constraintCount <= std::size(constraintsByType));
    assert(movieCount <= database.size());

    MovieLevel level;

    for (;;) {
      level.constraints.clear();
      level.movies.clear();

      // choose constraint types

      std::vector<std::size_t> constraintTypeIndices(std::size(constraintsByType));
      std::iota(constraintTypeIndices.begin(), constraintTypeIndices.end(), 0);
      std::shuffle(constraintTypeIndices.begin(), constraintTypeIndices.end(), random.getEngine());
      constraintTypeIndices.resize(constraintCount);

      // choose constraints

      for (auto typeIndex : constraintTypeIndices) {
        const auto& constraints = constraintsByType[typeIndex];
        assert(!constraints.empty());
        level.constraints.push_back(constraints[random.computeUniformInteger(std::size_t(0), constraints.size() - 1)]);
      }

      // classify movies

      std::vector<MovieData> acceptedMovies;
      std::vector<MovieData> rejectedMovies;

      for (auto& movie : database) {
        if (isMovieAcceptable(movie, level.constraints)) {
          acceptedMovies.push_back(movie);
        } else {
          rejectedMovies.push_back(movie);
        }
      }

      // check if there is enough accepted movies

      std::size_t minAcceptedMovies = 1 + movieCount / 5;
      std::size_t maxAcceptedMovies = 1 + movieCount / 2;

      if (acceptedMovies.size() < minAcceptedMovies) {
        // there is not enough accepted movies for this set of constraints
        // do it again
        continue;
      }

      // choose movies

      std::shuffle(acceptedMovies.begin(), acceptedMovies.end(), random.getEngine());
      std::shuffle(rejectedMovies.begin(), rejectedMovies.end(), random.getEngine());

      if (acceptedMovies.size() > maxAcceptedMovies) {
        acceptedMovies.resize(maxAcceptedMovies);
      }

      level.movies = acceptedMovies;
      assert(movieCount - acceptedMovies.size() <= rejectedMovies.size());

      for (std::size_t i = 0; i < movieCount - acceptedMovies.size(); ++i) {
        level.movies.push_back(rejectedMovies[i]);
      }

      std::shuffle(level.movies.begin(), level.movies.end(), random.getEngine());
      break;
    }

    return level;
  }

}
