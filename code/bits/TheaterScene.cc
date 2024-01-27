#include "TheaterScene.h"

#include "GameHub.h"
#include "GameData.h"

namespace mm {

  TheaterScene::TheaterScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_background(game)
  , m_movieManager(game)
  , m_broadcastButton(game.resources.getTexture("icons/check-solid.png"), gf::Color::Green, gf::Color::lighter(gf::Color::Green), gf::Color::darker(gf::Color::Green))
  , m_trashButton(game.resources.getTexture("icons/xmark-solid.png"), gf::Color::Red, gf::Color::lighter(gf::Color::Red), gf::Color::darker(gf::Color::Red))
  , m_recallButton(game.resources.getTexture("icons/note-sticky-regular.png"), gf::Color::Azure, gf::Color::lighter(gf::Color::Azure), gf::Color::darker(gf::Color::Azure))
  {
    setClearColor(gf::Color::Black);

    addWorldEntity(m_background);
    addWorldEntity(m_movieManager);

    // Widgets
    m_broadcastButton.setPosition(WorldSize * gf::vec(0.25f, 0.95f));
    m_broadcastButton.setAnchor(gf::Anchor::BottomRight);
    m_broadcastButton.setScale(0.8f);
    m_broadcastButton.setCallback([this](){
      if (m_game.state.movieState == MovieState::WaitingMovie) {
        if (isMovieAcceptable(m_game.state.movieLevel.movies[m_game.state.currentMovie], m_game.state.movieLevel.constraints)) {
          m_game.state.monsterState = MonsterState::Happy;
        } else {
          m_game.state.monsterState = MonsterState::Angry;
        }

        ++m_game.state.currentMovie;
        m_game.state.movieState = MovieState::DepartureMovie;
      }
    });
    m_widgets.addWidget(m_broadcastButton);

    m_trashButton.setPosition(WorldSize * gf::vec(0.30f, 0.95f));
    m_trashButton.setAnchor(gf::Anchor::BottomLeft);
    m_trashButton.setScale(0.8f);
    m_trashButton.setCallback([this](){
      if (m_game.state.movieState == MovieState::WaitingMovie) {
        if (isMovieAcceptable(m_game.state.movieLevel.movies[m_game.state.currentMovie], m_game.state.movieLevel.constraints)) {
          m_game.state.monsterState = MonsterState::Angry;
        } else {
          m_game.state.monsterState = MonsterState::Happy;
        }

        ++m_game.state.currentMovie;
        m_game.state.movieState = MovieState::DepartureMovie;
      }
    });
    m_widgets.addWidget(m_trashButton);

    m_recallButton.setPosition(WorldSize * gf::vec(0.02f, 0.02f));
    m_recallButton.setAnchor(gf::Anchor::TopLeft);
    m_recallButton.setScale(0.5f);
    m_recallButton.setCallback([this](){
      m_game.pushScene(m_game.listRecall);
    });
    m_widgets.addWidget(m_recallButton);

    setWorldViewSize(WorldSize);
    setWorldViewCenter(WorldSize * 0.5f);
  }

  void TheaterScene::doProcessEvent(gf::Event& event) {
    if (!isActive()) {
      return;
    }

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

  void TheaterScene::doUpdate([[maybe_unused]] gf::Time time) {
    if (m_game.state.movieState == MovieState::WaitingMovie) {
      if (m_broadcastButton.isDisabled()) {
        m_broadcastButton.setDefault();
      }

      if (m_trashButton.isDisabled()) {
        m_trashButton.setDefault();
      }
    } else {
      m_broadcastButton.setDisabled();
      m_trashButton.setDisabled();
    }
  }

  void TheaterScene::doRender(gf::RenderTarget& target, const gf::RenderStates &states) {
    if (!isActive()) {
      return;
    }

    renderWorldEntities(target, states);

    m_widgets.render(target, states);

    renderHudEntities(target, states);
  }

}
