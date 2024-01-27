#ifndef MM_THEATER_SCENE_H
#define MM_THEATER_SCENE_H

#include <gf/Scene.h>
#include <gf/WidgetContainer.h>

#include "FeedbackEntity.h"
#include "IconWidget.h"
#include "MovieManager.h"
#include "TheaterBackgroundEntity.h"

namespace mm {

  struct GameHub;

  class TheaterScene: public gf::Scene {
  public:
    TheaterScene(GameHub& game);

    void doProcessEvent(gf::Event& event) override;
    void doUpdate(gf::Time time) override;
    void doRender(gf::RenderTarget& target, const gf::RenderStates &states) override;

  private:
    GameHub& m_game;
    TheaterBackgroundEntity m_background;
    MovieManager m_movieManager;
    FeedbackEntity m_feedback;

    // Widgets
    IconWidget m_broadcastButton;
    IconWidget m_trashButton;
    IconWidget m_recallButton;
    gf::Vector2f m_lastPointer = { 0.0f, 0.0f };
    gf::WidgetContainer m_widgets;
  };

}


#endif // MM_THEATER_SCENE_H
