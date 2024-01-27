#ifndef MM_GAME_STATE_H
#define MM_GAME_STATE_H

#include <cstdint>

#include <gf/Path.h>

namespace mm {

  enum class MovieState : std::uint8_t {
    NoMovie,
    ArrivingMovie,
    WaitingMovie,
    DepartureMovie,
  };

  struct GameState {
    static constexpr uint16_t Version = 1;

    MovieState movieState = MovieState::NoMovie;

    void loadFromFile(const gf::Path& filename);
    void saveToFile(const gf::Path& filename);
  };

  template<typename Archive>
  Archive& operator|(Archive& ar, GameState& state) {
    return ar | state.movieState;
  }

}


#endif // MM_GAME_STATE_H
