#include "Office.h"

#include <gf/Coordinates.h>
#include <gf/Shapes.h>

namespace xy {

  void Office::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coords(target);
    gf::RectangleShape rect;
    rect.setColor(gf::Color::Yellow);
    rect.setSize(coords.getWindowSize() * gf::vec(0.5f, 1.0f));
    rect.setPosition(gf::vec(coords.getWindowSize().width * 0.5f, 0.0f));
    rect.draw(target, states);
  }

}
