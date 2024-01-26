#include "TheaterScene.h"

#include "GameHub.h"
#include "GameData.h"

namespace mm {
  TheaterScene::TheaterScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_background(game.resources)
  , m_movieManager(game.resources)
  {
    setClearColor(gf::Color::White);

    // addWorldEntity(m_background);
    addWorldEntity(m_movieManager);

    setWorldViewSize(WorldSize);
    setWorldViewCenter(WorldSize * 0.5f);
  }

}
