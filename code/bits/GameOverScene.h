#ifndef MM_GAME_OVER_SCENE_H
#define MM_GAME_OVER_SCENE_H

#include <gf/Scene.h>
#include <gf/WidgetContainer.h>

#include "GameOverEntity.h"
#include "IconWidget.h"

namespace mm {

  struct GameHub;

  class GameOverScene: public gf::Scene {
  public:
    GameOverScene(GameHub& game);

    void doProcessEvent(gf::Event& event) override;
    void doRender(gf::RenderTarget& target, const gf::RenderStates &states) override;

  private:
    GameHub& m_game;

    GameOverEntity m_entity;

    IconWidget m_retryButton;
    gf::WidgetContainer m_widgets;
  };

}


#endif // MM_GAME_OVER_SCENE_H
