#include "GameOverScene.h"

#include "GameHub.h"
#include "GameData.h"

namespace mm {

  GameOverScene::GameOverScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_entity(game)
  , m_retryButton(game.resources.getTexture("icons/rotate-right-solid.png"), gf::Color::Azure, gf::Color::lighter(gf::Color::Azure), gf::Color::darker(gf::Color::Azure))
  {
    setClearColor(gf::Color::Black);

    addWorldEntity(m_entity);

    m_retryButton.setPosition(WorldSize * gf::vec(0.50f, 0.90f));
    m_retryButton.setAnchor(gf::Anchor::BottomCenter);
    m_retryButton.setScale(0.5f);
    m_retryButton.setCallback([this](){
      gf::Ref<gf::Scene> scenes[2] = { m_game.common, m_game.start };
      m_game.replaceAllScenes(scenes);
    });
    m_widgets.addWidget(m_retryButton);

    setWorldViewSize(WorldSize);
    setWorldViewCenter(WorldSize * 0.5f);
  }

  void GameOverScene::doProcessEvent(gf::Event& event) {
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

  void GameOverScene::doRender(gf::RenderTarget& target, const gf::RenderStates &states) {
    renderWorldEntities(target, states);
    renderHudEntities(target, states);
    if (m_entity.hasFinishedCutScene()) {
      m_game.getRenderer().setView(getWorldView()); // HACK
      m_widgets.render(target, states);
    }
  }

}
