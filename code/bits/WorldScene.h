#ifndef XY_WORLD_SCENE_H
#define XY_WORLD_SCENE_H

#include <gf/Action.h>
#include <gf/Scene.h>
#include <gf/View.h>

#include "HeroEntity.h"
#include "MapEntity.h"
#include "PhysicsModel.h"

namespace xy {

  struct GameHub;

  class WorldScene : public gf::Scene {
  public:
    WorldScene(GameHub& game);

  private:
    void doProcessEvent(gf::Event& event) override;
    void doHandleActions(gf::Window& window) override;
    void doUpdate(gf::Time time) override;

  private:
    GameHub& m_game;
    gf::ZoomingViewAdaptor m_zoom;

    gf::Action m_leftAction;
    gf::Action m_rightAction;
    gf::Action m_jumpAction;

    PhysicsModel m_physicsModel;

    MapEntity m_mapEntity;
    HeroEntity m_heroEntity;
  };

}

#endif // XY_WORLD_SCENE_H
