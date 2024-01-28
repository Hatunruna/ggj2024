#include "DebriefScene.h"

#include "GameHub.h"
#include "GameData.h"

namespace mm {

  DebriefScene::DebriefScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , debrief(game)
  , m_okButton(game.resources.getTexture("icons/note-sticky-regular.png"), gf::Color::Azure, gf::Color::lighter(gf::Color::Azure), gf::Color::darker(gf::Color::Azure))
  {
    setClearColor(gf::Color::Black);

    addHudEntity(debrief);

    // Widgets
    m_okButton.setPosition(WorldSize * gf::vec(0.50f, 0.90f));
    m_okButton.setAnchor(gf::Anchor::BottomCenter);
    m_okButton.setScale(0.5f);
    m_okButton.setCallback([this](){
      if (m_game.state.currentLevel < (static_cast<int>(m_game.data.levelSettings.size()) - 1)) {
        ++m_game.state.currentLevel;
        m_game.startNewShift();
        m_game.replaceScene(m_game.listFirst);
      } else {
        m_game.replaceScene(m_game.gameOver);
      }
    });
    m_widgets.addWidget(m_okButton);

    setWorldViewSize(WorldSize);
    setWorldViewCenter(WorldSize * 0.5f);
  }

  void DebriefScene::doProcessEvent(gf::Event& event) {
    switch (event.type) {
    case gf::EventType::MouseMoved:
      m_widgets.pointTo(m_game.getRenderer().mapPixelToCoords(event.mouseCursor.coords, getWorldView()));
      break;

    case gf::EventType::MouseButtonPressed:
      m_widgets.pointTo(m_game.getRenderer().mapPixelToCoords(event.mouseButton.coords, getWorldView()));
      m_widgets.triggerAction();
      break;

    default:
      break;
    }
  }

  void DebriefScene::doRender(gf::RenderTarget& target, const gf::RenderStates &states) {
    renderWorldEntities(target, states);
    renderHudEntities(target, states);
    m_game.getRenderer().setView(getWorldView()); // HACK
    m_widgets.render(target, states);
  }

}
