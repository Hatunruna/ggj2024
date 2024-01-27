#include "DebriefScene.h"

#include "GameHub.h"
#include "GameData.h"

namespace mm {

  DebriefScene::DebriefScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_okButton("Ok!", game.resources.getFont("fonts/GoudyBookletter1911.otf"), 128)
  {
    setClearColor(gf::Color::Black);

    // Widgets
    m_okButton.setDefaultBackgroundColor(gf::Color::Azure);
    m_okButton.setDefaultTextColor(gf::Color::Black);
    m_okButton.setPosition(WorldSize * gf::vec(0.50f, 0.95f));
    m_okButton.setAnchor(gf::Anchor::BottomCenter);
    m_okButton.setScale(2.0f);
    m_okButton.setRadius(15.0f);
    m_okButton.setPadding(20.0f);
    m_okButton.setCallback([this](){
      if (m_game.startNewShift()) {
        m_game.replaceScene(m_game.listFirst);
      } else {
        // End Game...
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
    m_widgets.render(target, states);

    renderHudEntities(target, states);
  }

}
