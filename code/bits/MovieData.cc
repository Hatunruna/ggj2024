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
        return "The movie was released int a leap year";
      case MovieConstraint::YearIsNotLeap:
        return "The movie was released int a non-leap year";
      case MovieConstraint::YearIsOdd:
        return "The movie was released int a odd year";
      case MovieConstraint::YearIsEven:
        return "The movie was released int an even year";
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

  std::vector<MovieConstraint> computeConstraints(std::size_t count, gf::Random& random) {
    return {};
  }

  constexpr bool isLeap(int year) {
    return (year % 100 == 0) ? (year % 400 == 0) : (year % 4 == 0);
  }

  bool isMovieAcceptable(const MovieData& film, MovieConstraint constraint) {
    switch (constraint) {
      // title
      // year
      case MovieConstraint::YearAfter1980:
        return film.year >= 1980;
      case MovieConstraint::YearAfter1990:
        return film.year >= 1990;
      case MovieConstraint::YearAfter2000:
        return film.year >= 2000;
      case MovieConstraint::YearAfter2010:
        return film.year >= 2010;
      case MovieConstraint::YearBefore1990:
        return film.year <= 1990;
      case MovieConstraint::YearBefore2000:
        return film.year <= 2000;
      case MovieConstraint::YearBefore2010:
        return film.year <= 2010;
      case MovieConstraint::YearBefore2020:
        return film.year <= 2020;
      case MovieConstraint::YearIsLeap:
        return isLeap(film.year);
      case MovieConstraint::YearIsNotLeap:
        return !isLeap(film.year);
      case MovieConstraint::YearIsOdd:
        return film.year % 2 != 0;
      case MovieConstraint::YearIsEven:
        return film.year % 2 == 0;
      // duration
      case MovieConstraint::DurationMoreThan90:
        return film.duration >= 90;
      case MovieConstraint::DurationMoreThan120:
        return film.duration >= 120;
      case MovieConstraint::DurationMoreThan150:
        return film.duration >= 150;
      case MovieConstraint::DurationLessThan120:
        return film.duration <= 120;
      case MovieConstraint::DurationLessThan150:
        return film.duration <= 150;
      case MovieConstraint::DurationLessThan180:
        return film.duration <= 180;
      // note
      case MovieConstraint::NoteMoreThan2:
        return film.note >= 2;
      case MovieConstraint::NoteMoreThan3:
        return film.note >= 3;
      case MovieConstraint::NoteMoreThan4:
        return film.note >= 4;
      case MovieConstraint::NoteLessThan2:
        return film.note <= 2;
      case MovieConstraint::NoteLessThan3:
        return film.note <= 3;
      case MovieConstraint::NoteLessThan4:
        return film.note <= 4;
      // country
      // genre
      // technique
      case MovieConstraint::TechniqueIsAnimation:
        return film.technique == MovieTechnique::Animation;
      case MovieConstraint::TechniqueIsLiveAction:
        return film.technique == MovieTechnique::LiveAction;
      case MovieConstraint::TechniqueIsStopMotion:
        return film.technique == MovieTechnique::StopMotion;
      case MovieConstraint::TechniqueIsNotAnimation:
        return film.technique != MovieTechnique::Animation;
      case MovieConstraint::TechniqueIsNotLiveAction:
        return film.technique != MovieTechnique::LiveAction;
      case MovieConstraint::TechniqueIsNotStopMotion:
        return film.technique != MovieTechnique::StopMotion;
    }

    return true;
  }

}
