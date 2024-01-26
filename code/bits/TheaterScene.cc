#include "TheaterScene.h"

#include "GameHub.h"

namespace mm {
  TheaterScene::TheaterScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  {
    setClearColor(gf::Color::Black);

    setWorldViewCenter(game.getRenderer().getSize() * gf::vec(0.5f, 0.5f));
  }

}
