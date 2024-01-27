#ifndef MM_GAME_STATE_H
#define MM_GAME_STATE_H

#include <cstdint>

#include <gf/Path.h>

#include "MovieData.h"

namespace mm {

  enum class MovieState : std::uint8_t {
    NoMovie,
    ArrivingMovie,
    WaitingMovie,
    DepartureMovie,
  };

  enum class MonsterState : std::uint8_t {
    Neutral,
    Angry,
    Happy,
  };

  struct GameState {
    static constexpr uint16_t Version = 1;

    MovieState movieState = MovieState::NoMovie;
    MonsterState monsterState = MonsterState::Neutral;
    int currentLevel = 0;

    MovieLevel movieLevel;
    int currentMovie = 0;
    int correctChoices = 0;
    int incorrectChoices = 0;

    void loadFromFile(const gf::Path& filename);
    void saveToFile(const gf::Path& filename);
  };

  template<typename Archive>
  Archive& operator|(Archive& ar, GameState& state) {
    return ar | state.movieState | state.monsterState;
  }

}


#endif // MM_GAME_STATE_H
