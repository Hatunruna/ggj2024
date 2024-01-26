#ifndef MM_THEATER_SCENE_H
#define MM_THEATER_SCENE_H

#include <gf/Scene.h>

#include "Projector.h"
#include "Office.h"
#include "TheaterRoom.h"

namespace mm {

  struct GameHub;

  class TheaterScene: public gf::Scene {
  public:
    TheaterScene(GameHub& game);

  private:
    GameHub& m_game;
    TheaterRoom m_room;
    Office m_office;
    Projector m_projector;
  };

}


#endif // MM_THEATER_SCENE_H
