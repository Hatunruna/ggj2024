#include "TheaterBackgroundEntity.h"

#include <gf/Sprite.h>

namespace mm {

  TheaterBackgroundEntity::TheaterBackgroundEntity(gf::ResourceManager& resources)
  : m_theaterBackgroundTexture(resources.getTexture("images/theater-background.png"))
  , m_officeBackgroundTexture(resources.getTexture("images/office-background.png"))
  {}

  void TheaterBackgroundEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Sprite theaterBackground;
    theaterBackground.setTexture(m_theaterBackgroundTexture);
    theaterBackground.draw(target, states);

    gf::Sprite officeBackground;
    officeBackground.setTexture(m_officeBackgroundTexture);
    officeBackground.draw(target, states);
  }

}
