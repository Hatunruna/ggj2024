#include "FilmData.h"

#include <fstream>

#include <nlohmann/json.hpp>

namespace mm {

  NLOHMANN_JSON_SERIALIZE_ENUM(FilmCountry, {
    { FilmCountry::Canterlot, "Canterlot" },
    { FilmCountry::Gallifrey, "Gallifrey" },
    { FilmCountry::Hyrule, "Hyrule" },
    { FilmCountry::Innistrad, "Innistrad" },
    { FilmCountry::Morrowind, "Morrowind" },
    { FilmCountry::Temeria, "Temeria" },
    { FilmCountry::Valinor, "Valinor" },
    { FilmCountry::Wonderland, "Wonderland" },
  })

  NLOHMANN_JSON_SERIALIZE_ENUM(FilmGenre, {
    { FilmGenre::Action, "Action" },
    { FilmGenre::Comedy, "Comedy" },
    { FilmGenre::Drama, "Drama" },
    { FilmGenre::Fantasy, "Fantasy" },
    { FilmGenre::Horror, "Horror" },
    { FilmGenre::Musical, "Musical" },
    { FilmGenre::Romance, "Romance" },
    { FilmGenre::ScienceFiction, "ScienceFiction" },
    { FilmGenre::Western, "Western" },
  })

  NLOHMANN_JSON_SERIALIZE_ENUM(FilmTechnique, {
    { FilmTechnique::Animated, "Animated" },
    { FilmTechnique::LiveAction, "LiveAction" },
    { FilmTechnique::StopMotion, "StopMotion" },
  })

  NLOHMANN_JSON_SERIALIZE_ENUM(FilmRating, {
    { FilmRating::AllAges, "0+" },
    { FilmRating::Above12, "12+" },
    { FilmRating::Above16, "16+" },
    { FilmRating::Above18, "18+" },
  })

  void from_json(const nlohmann::json& j, FilmData& data) {
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

  std::vector<FilmData> load_database(gf::ResourceManager& resources, gf::Random& random) {
    std::vector<FilmData> db;

    auto filename = resources.getAbsolutePath("database.json");
    std::ifstream ifs(filename);
    nlohmann::json::parse(ifs).get_to(db);

    for (auto& film : db) {
      film.generated_by_ai = random.computeBernoulli(0.25);
    }

    return db;
  }

}
