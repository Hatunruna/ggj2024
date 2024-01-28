#ifndef MM_GAME_OVER_SCENE_H
#define MM_GAME_OVER_SCENE_H

#include <gf/Scene.h>

#include "GameOverEntity.h"

namespace mm {

  struct GameHub;

  class GameOverScene: public gf::Scene {
  public:
    GameOverScene(GameHub& game);

  private:
    GameHub& m_game;

    GameOverEntity m_entity;
  };

}


#endif // MM_GAME_OVER_SCENE_H
