#ifndef MM_FEEDBACK_ENTITY_H
#define MM_FEEDBACK_ENTITY_H

#include <gf/Entity.h>
#include <gf/Font.h>

namespace mm {
  struct GameHub;
  struct GameState;

  class FeedbackEntity : public gf::Entity {
  public:
    FeedbackEntity(GameHub& game);

    void reset();

    void update(gf::Time time) override;
    void render(gf::RenderTarget &target, const gf::RenderStates &states) override;
  private:
    GameHub& m_gameHub;
    gf::Font& m_font;
    gf::Texture& m_movieTexture;
    gf::Texture& m_timerTexture;
  };

}

#endif // MM_FEEDBACK_ENTITY_H
