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

  enum class MonsterState {
    Neutral,
    Angry,
    Happy,
  };

  struct GameData {
    MovieState movieState = MovieState::NoMovie;
    float movieAngle = 0.0f;

    MonsterState monsterState = MonsterState::Neutral;
  };

}

#endif // MM_GAME_DATA_H
