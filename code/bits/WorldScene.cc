#include "WorldScene.h"

#include <gf/Color.h>
#include <gf/Keyboard.h>

#include "GameHub.h"

namespace xy {

  WorldScene::WorldScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_zoom(game.getRenderer(), getWorldView())
  , m_leftAction("Left")
  , m_rightAction("Right")
  , m_jumpAction("Jump")
  , m_physicsModel(game.state)
  , m_mapEntity(game.state.map)
  , m_heroEntity(game.state.hero)
  {
    setClearColor(gf::Color::White);

    m_leftAction.addKeycodeKeyControl(gf::Keycode::Left);
    m_leftAction.setContinuous();
    addAction(m_leftAction);

    m_rightAction.addKeycodeKeyControl(gf::Keycode::Right);
    m_rightAction.setContinuous();
    addAction(m_rightAction);

    m_jumpAction.addKeycodeKeyControl(gf::Keycode::Space);
    m_jumpAction.setInstantaneous();
    addAction(m_jumpAction);

    addModel(m_physicsModel);
    addWorldEntity(m_mapEntity);
    addWorldEntity(m_heroEntity);
  }

  void WorldScene::doProcessEvent(gf::Event& event)
  {
    m_zoom.processEvent(event);
  }

  void WorldScene::doHandleActions([[maybe_unused]] gf::Window& window)
  {
    if (!isActive()) {
      return;
    }

    if (m_leftAction.isActive()) {
      m_game.state.hero.body.move(gf::Orientation::East);
    } else if (m_rightAction.isActive()) {
      m_game.state.hero.body.move(gf::Orientation::West);
    } else {
      m_game.state.hero.body.move(gf::Orientation::Center);
    }

    if (m_jumpAction.isActive()) {
      m_game.state.hero.body.jump();
    }

  }

  void WorldScene::doUpdate([[maybe_unused]] gf::Time time)
  {
    setWorldViewCenter(m_game.state.hero.body.position);
  }

}
