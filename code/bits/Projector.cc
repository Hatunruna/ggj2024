#include "Projector.h"

#include <gf/Coordinates.h>
#include <gf/Shapes.h>

namespace xy {

  void Projector::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coords(target);
    gf::RectangleShape rect;
    rect.setColor(gf::Color::Violet);
    rect.setSize(coords.getWindowSize() * gf::vec(0.2f, 1.0f));
    const gf::Vector2f offset = coords.getWindowSize() * gf::dirx(0.4f);
    rect.setPosition(gf::vec(offset.x, 0.0f));
    rect.draw(target, states);
  }

}
