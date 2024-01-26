#include "TheaterRoom.h"

#include <gf/Coordinates.h>
#include <gf/Shapes.h>

namespace mm {
  void TheaterRoom::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coords(target);
    gf::RectangleShape rect;
    rect.setColor(gf::Color::Blue);
    rect.setSize(coords.getWindowSize() * gf::vec(0.5f, 1.0f));
    rect.draw(target, states);
  }
}
