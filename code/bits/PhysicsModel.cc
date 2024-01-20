#include "PhysicsModel.h"

#include <gf/Collision.h>
#include <gf/Rect.h>
#include <gf/Vector.h>
#include <gf/VectorOps.h>

#include "GameState.h"
#include "Constants.h"

namespace xy {

  PhysicsModel::PhysicsModel(GameState& state)
  : m_state(state)
  {
  }

  void PhysicsModel::update(gf::Time time)
  {
    // apply gravity
    auto& hero = m_state.hero.body;
    hero.velocity += Gravity * time.asSeconds();
    hero.position += hero.velocity * time.asSeconds();
    hero.colliding = false;

    gf::RectF heroBounds = gf::RectF::fromCenterSize(hero.position, hero.size);

    // check collision
    gf::Vector2i coordinates = hero.position / TileSize;

    for (int dy = -3; dy <= 3; ++dy) {
      for (int dx = -2; dx <= 2; ++dx) {
        auto cellCoordinates = coordinates + gf::vec(dx, dy);

        if (!m_state.map.cells.isValid(cellCoordinates)) {
          continue;
        }

        auto& cell = m_state.map.cells(cellCoordinates);

        if (cell.biome == Biome::Void) {
          continue;
        }

        gf::RectF cellBounds = gf::RectF::fromPositionSize(cellCoordinates * TileSize, TileSize);
        gf::Penetration penetration = {};

        if (gf::collides(cellBounds, heroBounds, penetration)) {
          hero.colliding = true;
          hero.position += penetration.depth * penetration.normal * 0.5f;
          hero.velocity -= gf::dot(hero.velocity, penetration.normal) * penetration.normal;
        }
      }
    }

  }

}
