#include "CommonScene.h"

#include <gf/Log.h>

#include "GameHub.h"

namespace mm {

  CommonScene::CommonScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_fullscreenAction("Fullscreen")
  {
    setClearColor(gf::Color::Black);

    m_fullscreenAction.addKeycodeKeyControl(gf::Keycode::F);
    m_fullscreenAction.addKeycodeKeyControl(gf::Keycode::F11);
    addAction(m_fullscreenAction);

    addHudEntity(game.sounds);
  }

  void CommonScene::doHandleActions(gf::Window& window) {
    if (m_fullscreenAction.isActive()) {
      window.toggleFullscreen();
    }
  }

}
