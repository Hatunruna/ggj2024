#ifndef XY_WORLD_SCENE_H
#define XY_WORLD_SCENE_H

#include <gf/Action.h>
#include <gf/Scene.h>
#include <gf/View.h>

#include "MapEntity.h"

namespace xy {

  struct GameHub;

  class WorldScene : public gf::Scene {
  public:
    WorldScene(GameHub& game);

  private:
    void doProcessEvent(gf::Event& event) override;
    void doHandleActions(gf::Window& window) override;

  private:
    GameHub& m_game;
    gf::ZoomingViewAdaptor m_zoom;

    MapEntity m_mapEntity;
  };

}

#endif // XY_WORLD_SCENE_H
