#include "MapEntity.h"

namespace xy {

  namespace {
    constexpr float CellSize = 128.0f;

    std::size_t countVertices(const MapState& state)
    {
      auto size = state.cells.getSize();
      return size.width * size.height * 6;
    }

  }

  MapEntity::MapEntity(MapState& state)
  : m_state(state)
  , m_vertices(gf::PrimitiveType::Triangles, countVertices(state))
  {
    for (auto position : state.cells.getPositionRange()) {
      setBiome(position, state.cells(position).biome);
    }
  }

  void MapEntity::setBiome(gf::Vector2i position, Biome biome)
  {
    gf::Color4f color = gf::Color::Black;

    switch (biome) {
      case Biome::Void:
        color = gf::Color::Azure;
        break;
      case Biome::Gravel:
        color = gf::Color::fromRgba32(0x964C29FF);
        break;
      case Biome::Stone:
        color = gf::Color::Gray();
        break;
    }

    auto bounds = gf::RectI::fromPositionSize(position, { 1, 1 });

    gf::Vertex vertices[4] = {
      { bounds.getTopLeft() * CellSize, color, { 0.0f, 0.0f } },
      { bounds.getTopRight() * CellSize, color, { 0.0f, 0.0f } },
      { bounds.getBottomLeft() * CellSize, color, { 0.0f, 0.0f } },
      { bounds.getBottomRight() * CellSize, color, { 0.0f, 0.0f } },
    };

    std::size_t index = (position.x + m_state.cells.getCols() * position.y) * 6;
    assert(index + 6 <= m_vertices.getVertexCount());

    m_vertices[index + 0] = vertices[0];
    m_vertices[index + 1] = vertices[1];
    m_vertices[index + 2] = vertices[2];

    m_vertices[index + 3] = vertices[2];
    m_vertices[index + 4] = vertices[1];
    m_vertices[index + 5] = vertices[3];
  }

  void MapEntity::render(gf::RenderTarget& target, const gf::RenderStates& states)
  {
    m_vertices.draw(target, states);
  }

}
