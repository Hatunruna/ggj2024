#include "ConstraintListScene.h"

#include "GameHub.h"
#include "GameData.h"

namespace mm {

  ConstraintListScene::ConstraintListScene(GameHub& game, ConstraintListType type)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_type(type)
  , m_requirementsEntity(game)
  , m_okButton(game.resources.getTexture("icons/video-solid.png"), gf::Color::Azure, gf::Color::lighter(gf::Color::Azure), gf::Color::Azure)
  {
    setClearColor(gf::Color::Black);

    addHudEntity(m_requirementsEntity);

    // Widgets
    m_okButton.setPosition(WorldSize * gf::vec(0.50f, 0.90f));
    m_okButton.setAnchor(gf::Anchor::BottomCenter);
    m_okButton.setScale(0.5f);
    m_okButton.setCallback([this](){
      if (m_type == ConstraintListType::First) {
        m_game.replaceScene(m_game.theater);
        m_game.sounds.startTheaterAmbiance();
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
    renderHudEntities(target, states);
    m_game.getRenderer().setView(getWorldView()); // HACK
    m_widgets.render(target, states);
  }

}
