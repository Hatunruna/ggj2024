#ifndef MM_DEBRIEF_SCENE_H
#define MM_DEBRIEF_SCENE_H

#include <gf/Scene.h>
#include <gf/WidgetContainer.h>
#include <gf/Widgets.h>

namespace mm {

  struct GameHub;

  class DebriefScene: public gf::Scene {
  public:
    DebriefScene(GameHub& game);

    void doProcessEvent(gf::Event& event) override;
    void doRender(gf::RenderTarget& target, const gf::RenderStates &states) override;

  private:
    GameHub& m_game;

    // Widgets
    gf::TextButtonWidget m_okButton;
    gf::WidgetContainer m_widgets;
  };

}


#endif // MM_DEBRIEF_SCENE_H
