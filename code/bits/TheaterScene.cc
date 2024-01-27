#include "TheaterScene.h"

#include "GameHub.h"
#include "GameData.h"

namespace mm {

  TheaterScene::TheaterScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_background(game)
  , m_movieManager(game)
  , m_broadcastButton("Broadcast", game.resources.getFont("fonts/GoudyBookletter1911.otf"), 128)
  , m_trashButton("Trash", game.resources.getFont("fonts/GoudyBookletter1911.otf"), 128)
  {
    setClearColor(gf::Color::Black);

    addWorldEntity(m_background);
    addWorldEntity(m_movieManager);

    // Widgets
    m_broadcastButton.setDefaultBackgroundColor(gf::Color::Green);
    m_broadcastButton.setDefaultTextColor(gf::Color::Black);
    m_broadcastButton.setPosition(WorldSize * gf::vec(0.30f, 0.95f));
    m_broadcastButton.setAnchor(gf::Anchor::BottomRight);
    m_broadcastButton.setScale(2.0f);
    m_broadcastButton.setRadius(15.0f);
    m_broadcastButton.setPadding(20.0f);
    m_widgets.addWidget(m_broadcastButton);

    m_trashButton.setDefaultBackgroundColor(gf::Color::Red);
    m_trashButton.setDefaultTextColor(gf::Color::Black);
    m_trashButton.setPosition(WorldSize * gf::vec(0.45f, 0.95f));
    m_trashButton.setAnchor(gf::Anchor::BottomLeft);
    m_trashButton.setScale(2.0f);
    m_trashButton.setRadius(15.0f);
    m_trashButton.setPadding(20.0f);
    m_widgets.addWidget(m_trashButton);

    setWorldViewSize(WorldSize);
    setWorldViewCenter(WorldSize * 0.5f);
  }

  void TheaterScene::doProcessEvent(gf::Event& event) {
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

  void TheaterScene::doRender(gf::RenderTarget& target, const gf::RenderStates &states) {
    renderWorldEntities(target, states);
    m_widgets.render(target, states);

    renderHudEntities(target, states);
  }

}
