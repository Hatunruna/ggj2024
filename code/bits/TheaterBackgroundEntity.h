#ifndef MM_THEATER_BACKGROUND_ENTITY_H
#define MM_THEATER_BACKGROUND_ENTITY_H

#include <gf/Animation.h>
#include <gf/Entity.h>
#include <gf/ResourceManager.h>
#include <gf/Texture.h>

namespace mm {

  struct GameHub;
  struct GameState;

  class TheaterBackgroundEntity: public gf::Entity {
  public:
    TheaterBackgroundEntity(GameHub& game);

    virtual void update(gf::Time time) override;
    virtual void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    GameState& m_gameState;

    gf::Texture& m_theaterBackgroundTexture;

    std::vector<gf::Animation> m_angryAnimations;
    std::vector<gf::Animation> m_happyAnimations;
    gf::Texture& m_monsterPause;

    gf::Texture& m_officeBackgroundTexture;
  };

}

#endif // MM_THEATER_BACKGROUND_ENTITY_H
