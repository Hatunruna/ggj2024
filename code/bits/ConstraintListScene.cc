#include "ConstraintListScene.h"

#include "GameHub.h"
#include "GameData.h"

namespace mm {

  ConstraintListScene::ConstraintListScene(GameHub& game, ConstraintListType type)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_type(type)
  , m_requirementsEntity(game)
  , m_okButton("Ok!", game.resources.getFont("fonts/GoudyBookletter1911.otf"), 128)
  {
    setClearColor(gf::Color::Black);

    addHudEntity(m_requirementsEntity);

    // Widgets
    m_okButton.setDefaultBackgroundColor(gf::Color::Azure);
    m_okButton.setDefaultTextColor(gf::Color::Black);
    m_okButton.setPosition(WorldSize * gf::vec(0.50f, 0.95f));
    m_okButton.setAnchor(gf::Anchor::BottomCenter);
    m_okButton.setScale(2.0f);
    m_okButton.setRadius(15.0f);
    m_okButton.setPadding(20.0f);
    m_okButton.setCallback([this](){
      if (m_type == ConstraintListType::First) {
        m_game.replaceScene(m_game.theater);
      } else {
        m_game.popScene();
      }
    });
    m_widgets.addWidget(m_okButton);

    setWorldViewSize(WorldSize);
    setWorldViewCenter(WorldSize * 0.5f);
  }

  void ConstraintListScene::doProcessEvent(gf::Event& event) {
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

  void ConstraintListScene::doRender(gf::RenderTarget& target, const gf::RenderStates &states) {
    renderWorldEntities(target, states);
    m_widgets.render(target, states);

    renderHudEntities(target, states);
  }

}
