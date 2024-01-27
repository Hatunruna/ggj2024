#ifndef MM_THEATER_SCENE_H
#define MM_THEATER_SCENE_H

#include <gf/Scene.h>
#include <gf/WidgetContainer.h>
#include <gf/Widgets.h>

#include "MovieManager.h"
#include "TheaterBackgroundEntity.h"

namespace mm {

  struct GameHub;

  class TheaterScene: public gf::Scene {
  public:
    TheaterScene(GameHub& game);

    void doProcessEvent(gf::Event& event) override;
    void doRender(gf::RenderTarget& target, const gf::RenderStates &states) override;

  private:
    GameHub& m_game;
    TheaterBackgroundEntity m_background;
    MovieManager m_movieManager;

    // Widgets
    gf::TextButtonWidget m_broadcastButton;
    gf::TextButtonWidget m_trashButton;
    gf::TextButtonWidget m_recallButton;
    gf::WidgetContainer m_widgets;
  };

}


#endif // MM_THEATER_SCENE_H
