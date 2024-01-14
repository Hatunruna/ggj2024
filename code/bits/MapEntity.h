#ifndef XY_MAP_ENTITY_H
#define XY_MAP_ENTITY_H

#include <gf/Entity.h>
#include <gf/VertexArray.h>

#include "MapState.h"

namespace xy {
  class MapEntity : public gf::Entity {
  public:
    MapEntity(MapState& state);

    void setBiome(gf::Vector2i position, Biome biome);

    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    MapState& m_state;
    gf::VertexArray m_vertices;
  };

}

#endif // XY_MAP_ENTITY_H
