#ifndef MM_CONSTRAINT_LIST_SCENE_H
#define MM_CONSTRAINT_LIST_SCENE_H

#include <gf/Scene.h>
#include <gf/WidgetContainer.h>

#include "IconWidget.h"
#include "RequirementsEntity.h"

namespace mm {

  struct GameHub;

  enum class ConstraintListType {
    First,
    Recall,
  };

  class ConstraintListScene: public gf::Scene {
  public:
    ConstraintListScene(GameHub& game, ConstraintListType type);

    void doProcessEvent(gf::Event& event) override;
    void doRender(gf::RenderTarget& target, const gf::RenderStates &states) override;

  private:
    GameHub& m_game;
    ConstraintListType m_type;

    RequirementsEntity m_requirementsEntity;

    // Widgets
    IconWidget m_okButton;
    gf::WidgetContainer m_widgets;
  };

}


#endif // MM_CONSTRAINT_LIST_SCENE_H
