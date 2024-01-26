#ifndef MM_FILM_DATA_H
#define MM_FILM_DATA_H

#include <vector>
#include <string>

#include <gf/Random.h>
#include <gf/ResourceManager.h>

namespace mm {

  enum class FilmCountry {
    Canterlot,
    Gallifrey,
    Hyrule,
    Innistrad,
    Morrowind,
    Temeria,
    Valinor,
    Wonderland,
  };

  enum class FilmGenre {
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

  enum class FilmTechnique {
    Animated,
    LiveAction,
    StopMotion,
  };

  enum class FilmRating {
    AllAges,
    Above12,
    Above16,
    Above18,
  };

  struct FilmData {
    std::string title;
    int year = 0;
    int duration = 0;
    int note = 0;
    FilmCountry country;
    FilmGenre genre;
    FilmTechnique technique;
    FilmRating rating;
    std::vector<std::string> themes;
    bool generated_by_ai = false;
  };

  std::vector<FilmData> load_database(gf::ResourceManager& resources, gf::Random& random);

}

#endif // MM_FILM_DATA_H
