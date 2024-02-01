#ifndef MM_GAME_OVER_ENTITY_H
#define MM_GAME_OVER_ENTITY_H

#include <gf/Animation.h>
#include <gf/Entity.h>
#include <gf/Font.h>

namespace mm {

  struct GameHub;
  struct GameState;

  class GameOverEntity: public gf::Entity {
  public:
    GameOverEntity(GameHub& game);

    void update(gf::Time time) override;
    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

    bool hasFinishedCutScene() const;

  private:
    GameHub& m_game;
    gf::Font& m_font;
    gf::Texture& m_backgroundTexture;

    // Bad ending stuff
    gf::Texture& m_theaterBackgroundTexture;
    gf::Animation m_projectorAnimation;
    gf::Texture& m_officeBackgroundTexture;
    std::vector<gf::Animation> m_badEndingAnimations;
  };

}

#endif // MM_GAME_OVER_ENTITY_H
