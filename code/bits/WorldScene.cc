#include "WorldScene.h"

#include <gf/Color.h>

#include "GameHub.h"

namespace xy {

  WorldScene::WorldScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_zoom(game.getRenderer(), getWorldView())
  , m_mapEntity(game.state.map)
  {
    setClearColor(gf::Color::White);

//     m_startAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::A);
//     m_startAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::B);
//     m_startAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::X);
//     m_startAction.addGamepadButtonControl(gf::AnyGamepad, gf::GamepadButton::Y);

    addWorldEntity(m_mapEntity);
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
  }

}
