#ifndef MM_CONSTRAINT_LIST_SCENE_H
#define MM_CONSTRAINT_LIST_SCENE_H

#include <gf/Scene.h>
#include <gf/WidgetContainer.h>
#include <gf/Widgets.h>

#include "RequirementsEntity.h"

namespace mm {

  struct GameHub;

  class ConstraintListScene: public gf::Scene {
  public:
    ConstraintListScene(GameHub& game);

    void doProcessEvent(gf::Event& event) override;
    void doRender(gf::RenderTarget& target, const gf::RenderStates &states) override;

  private:
    GameHub& m_game;

    RequirementsEntity m_requirementsEntity;

    // Widgets
    gf::TextButtonWidget m_okButton;
    gf::WidgetContainer m_widgets;
  };

}


#endif // MM_CONSTRAINT_LIST_SCENE_H
