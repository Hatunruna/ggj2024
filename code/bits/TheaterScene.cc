#include "TheaterScene.h"

#include "GameHub.h"

namespace xy {
  TheaterScene::TheaterScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  {
    setClearColor(gf::Color::Black);

    addWorldEntity(m_room);
    addWorldEntity(m_office);
    addWorldEntity(m_projector);

    setWorldViewCenter(game.getRenderer().getSize() * gf::vec(0.5f, 0.5f));
  }

}
