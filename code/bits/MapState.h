#ifndef XY_MAP_STATE_H
#define XY_MAP_STATE_H

#include <gf/Array2D.h>
#include <gf/Random.h>

#include "Signal.h"

namespace xy {

  enum class Biome {
    Void,
    Gravel,
    Stone,
  };

  struct Cell {
    Biome biome = Biome::Void;
    int initial_life = 0;
    int current_life = 0;
  };

  struct MapState {
    MapState(gf::Random& random);

    Signal<void(gf::Vector2i, Biome)> change_biome;

    gf::Array2D<Cell, int> cells;
  };

}

#endif // XY_MAP_STATE_H
