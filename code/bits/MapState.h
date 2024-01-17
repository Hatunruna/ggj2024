#ifndef XY_MAP_STATE_H
#define XY_MAP_STATE_H

#include <gf/Array2D.h>
#include <gf/Random.h>

namespace xy {

  enum class Biome {
    Void,
    Gravel,
    Stone,
  };

  struct Cell {
    Biome biome = Biome::Void;
    int32_t initial_life = 0;
    int32_t current_life = 0;
  };

  template<typename Archive>
  Archive& operator|(Archive& ar, Cell& cell) {
    return ar | cell.biome | cell.initial_life | cell.current_life;
  }

  struct MapState {
    void generate(gf::Random& random);

    gf::Array2D<Cell, int> cells;
  };

  template<typename Archive>
  Archive& operator|(Archive& ar, MapState& state) {
    return ar | state.cells;
  }

}

#endif // XY_MAP_STATE_H
