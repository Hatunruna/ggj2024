#ifndef XY_THEATER_SCENE_H
#define XY_THEATER_SCENE_H

#include <gf/Scene.h>

#include "Projector.h"
#include "Office.h"
#include "TheaterRoom.h"

namespace xy {

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


#endif // XY_THEATER_SCENE_H
