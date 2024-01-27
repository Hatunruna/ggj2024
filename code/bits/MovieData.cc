#include "MovieData.h"

#include <cassert>
#include <fstream>

#include <nlohmann/json.hpp>

namespace mm {

  std::string toString(MovieCountry country) {
    switch (country) {
      case mm::MovieCountry::Canterlot:
        return "Canterlot";
      case mm::MovieCountry::Gallifrey:
        return "Gallifrey";
      case mm::MovieCountry::Hyrule:
        return "Hyrule";
      case mm::MovieCountry::Innistrad:
        return "Innistrad";
      case mm::MovieCountry::Morrowind:
        return "Morrowind";
      case mm::MovieCountry::Temeria:
        return "Temeria";
      case mm::MovieCountry::Valinor:
        return "Valinor";
      case mm::MovieCountry::Wonderland:
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
    j.at("year").get_to(data.year);
    j.at("duration").get_to(data.duration);
    j.at("note").get_to(data.note);
    j.at("country").get_to(data.country);
    j.at("genre").get_to(data.genre);
    j.at("technique").get_to(data.technique);
    j.at("rating").get_to(data.rating);
    j.at("themes").get_to(data.themes);
  }

  std::vector<MovieData> loadDatabase(gf::ResourceManager& resources, gf::Random& random) {
    std::vector<MovieData> db;

    auto filename = resources.getAbsolutePath("database.json");
    std::ifstream ifs(filename);
    nlohmann::json::parse(ifs).get_to(db);

    for (auto& film : db) {
      film.generated_by_ai = random.computeBernoulli(0.25);
    }

    return db;
  }

  std::string toString(MovieConstraint constraint) {
    switch (constraint) {
      // title
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
        return "The movie lasts more than 90 minutes";
      case MovieConstraint::DurationMoreThan120:
        return "The movie lasts more than 120 minutes";
      case MovieConstraint::DurationMoreThan150:
        return "The movie lasts more than 150 minutes";
      case MovieConstraint::DurationLessThan120:
        return "The movie lasts less than 120 minutes";
      case MovieConstraint::DurationLessThan150:
        return "The movie lasts less than 150 minutes";
      case MovieConstraint::DurationLessThan180:
        return "The movie lasts less than 180 minutes";
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
      // genre
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
      // genre
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
    }

    return true;
  }

  bool isMovieAcceptable(const MovieData& movie, const std::vector<MovieConstraint>& constraints) {
    return std::all_of(constraints.begin(), constraints.end(), [&](MovieConstraint constraint) {
      return isMovieAcceptable(movie, constraint);
    });
  }

  MovieLevel computeLevel(const std::vector<MovieData>& database, std::size_t constraintCount, std::size_t movieCount, gf::Random& random) {
    const std::vector<mm::MovieConstraint> constraintsByType[] = {
      // {
        // title
      // },
      {
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
      },
      {
        // duration
        mm::MovieConstraint::DurationMoreThan90,
        mm::MovieConstraint::DurationMoreThan120,
        mm::MovieConstraint::DurationMoreThan150,
        mm::MovieConstraint::DurationLessThan120,
        mm::MovieConstraint::DurationLessThan150,
        mm::MovieConstraint::DurationLessThan180,
      },
      {
        // note
        mm::MovieConstraint::NoteMoreThan2,
        mm::MovieConstraint::NoteMoreThan3,
        mm::MovieConstraint::NoteMoreThan4,
        mm::MovieConstraint::NoteLessThan2,
        mm::MovieConstraint::NoteLessThan3,
        mm::MovieConstraint::NoteLessThan4,
      },
      // {
        // country
      // },
      // {
        // genre
      // },
      {
        // technique
        mm::MovieConstraint::TechniqueIsAnimation,
        mm::MovieConstraint::TechniqueIsLiveAction,
        mm::MovieConstraint::TechniqueIsStopMotion,
        mm::MovieConstraint::TechniqueIsNotAnimation,
        mm::MovieConstraint::TechniqueIsNotLiveAction,
        mm::MovieConstraint::TechniqueIsNotStopMotion,
      },
      // {
        // rating
      // },
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
