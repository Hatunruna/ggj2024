#ifndef XY_GAME_HERO_ENTITY_H
#define XY_GAME_HERO_ENTITY_H

#include <gf/Entity.h>

namespace xy {
  struct HeroState;

  class HeroEntity : public gf::Entity {
  public:
    HeroEntity(HeroState& state);

    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    HeroState& m_state;
  };

}

#endif // XY_GAME_HERO_ENTITY_H
