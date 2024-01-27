#ifndef MM_REQUIREMENTS_ENTITY_H
#define MM_REQUIREMENTS_ENTITY_H

#include <gf/Entity.h>
#include <gf/Font.h>

namespace mm {

  struct GameHub;
  struct GameState;

  class RequirementsEntity: public gf::Entity {
  public:
    RequirementsEntity(GameHub& game);

    // void update(gf::Time time) override;
    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    GameState& m_gameState;
    gf::Font& m_font;
  };

}

#endif // MM_REQUIREMENTS_ENTITY_H
