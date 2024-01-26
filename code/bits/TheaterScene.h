#ifndef MM_THEATER_SCENE_H
#define MM_THEATER_SCENE_H

#include <gf/Scene.h>

namespace mm {

  struct GameHub;

  class TheaterScene: public gf::Scene {
  public:
    TheaterScene(GameHub& game);

  private:
    GameHub& m_game;
  };

}


#endif // MM_THEATER_SCENE_H
