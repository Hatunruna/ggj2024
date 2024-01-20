#ifndef XY_GAME_PHYSICS_MODEL_H
#define XY_GAME_PHYSICS_MODEL_H

#include <gf/Model.h>

namespace xy {
  struct GameState;

  class PhysicsModel : public gf::Model {
  public:
    PhysicsModel(GameState& state);

    void update(gf::Time time) override;

  private:
    GameState& m_state;
    bool m_hero_colliding = false;
  };

}

#endif // XY_GAME_PHYSICS_MODEL_H
