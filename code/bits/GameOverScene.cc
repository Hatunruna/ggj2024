#include "GameOverScene.h"

#include "GameHub.h"
#include "GameData.h"

namespace mm {

  GameOverScene::GameOverScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_entity(game)
  {
    setClearColor(gf::Color::Black);

    addHudEntity(m_entity);

    setWorldViewSize(WorldSize);
    setWorldViewCenter(WorldSize * 0.5f);
  }

}
