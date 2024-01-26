#include "TheaterScene.h"

#include "GameHub.h"
#include "GameData.h"

namespace mm {
  TheaterScene::TheaterScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_background(game.resources)
  {
    setClearColor(gf::Color::White);

    addWorldEntity(m_background);

    setWorldViewSize(WorldSize);
    setWorldViewCenter(WorldSize * 0.5f);
  }

}
