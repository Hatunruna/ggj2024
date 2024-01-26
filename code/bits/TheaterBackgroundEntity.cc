#include "TheaterBackgroundEntity.h"

#include <gf/Sprite.h>

namespace mm {

  TheaterBackgroundEntity::TheaterBackgroundEntity(gf::ResourceManager& resources)
  : m_backgroundTexture(resources.getTexture("images/background.png"))
  {}

  void TheaterBackgroundEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Sprite m_background;
    m_background.setTexture(m_backgroundTexture);
    m_background.draw(target, states);
  }

}
