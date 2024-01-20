#include "HeroEntity.h"

#include <gf/Rect.h>
#include <gf/RenderTarget.h>
#include <gf/Shapes.h>

#include "Constants.h"
#include "HeroState.h"

namespace xy {

  HeroEntity::HeroEntity(HeroState& state)
  : m_state(state)
  {
    m_state.body.position = gf::vec(MapWidth / 2, 0) * TileSize;
    m_state.body.size = gf::vec(TileSize.width, 1.8f * TileSize.height);
  }

  void HeroEntity::render(gf::RenderTarget& target, const gf::RenderStates& states)
  {
    gf::RectF bounds = gf::RectF::fromCenterSize(m_state.body.position, m_state.body.size);

    gf::RectangleShape heroShape(bounds);
    heroShape.setColor(gf::Color::Yellow);
    target.draw(heroShape, states);
  }

}
