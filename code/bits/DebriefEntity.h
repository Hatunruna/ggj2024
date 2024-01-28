#ifndef MM_DEBRIEF_ENTITY_H
#define MM_DEBRIEF_ENTITY_H

#include <gf/Entity.h>
#include <gf/Font.h>

namespace mm {

  struct GameHub;
  struct GameState;

  class DebriefEntity: public gf::Entity {
  public:
    DebriefEntity(GameHub& game);

    // void update(gf::Time time) override;
    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    GameHub& m_game;
    GameState& m_gameState;
    gf::Font& m_font;
  };

}

#endif // MM_DEBRIEF_ENTITY_H
