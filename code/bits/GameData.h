#ifndef MM_GAME_DATA_H
#define MM_GAME_DATA_H

#include <gf/Vector.h>

namespace mm {

  constexpr gf::Vector2i WorldSize = gf::vec(3840, 2160);

  enum class MovieState {
    NoMovie,
    ArrivingMovie,
    WaitingMovie,
    DepartureMovie,
  };

  struct GameData {
    MovieState movieState = MovieState::NoMovie;
    gf::Vector2f moviePosition = gf::vec(0.0f, 0.0f);
  };

}

#endif // MM_GAME_DATA_H
