#include "IconWidget.h"

#include <gf/RenderTarget.h>

namespace mm {

  IconWidget::IconWidget(const gf::Texture& texture, gf::Color4f defaultColor, gf::Color4f selectedColor, gf::Color4f disabledColor)
  : m_sprite(texture)
  , m_defaultColor(defaultColor)
  , m_selectedColor(selectedColor)
  , m_disabledColor(disabledColor)
  {
    updateGeometry();
  }

  void IconWidget::draw(gf::RenderTarget &target, const gf::RenderStates& states)
  {
    assert(m_sprite.hasTexture());

    gf::RenderStates localStates = states;
    localStates.transform *= getTransform();
    localStates.texture[0] = &m_sprite.getTexture();
    target.draw(m_vertices, 4, gf::PrimitiveType::TriangleStrip, localStates);
  }

  namespace {

    template<typename T, typename U>
    bool isInsideBounds(gf::Vector2f coords, const T& basic, const U& widget, gf::Vector2f offset = { 0.0f, 0.0f }) {
      gf::Vector2f local = gf::transform(widget.getInverseTransform(), coords);
      return basic.getLocalBounds().contains(local + offset);
    }

  }

  bool IconWidget::contains(gf::Vector2f coords)
  {
    return isInsideBounds(coords, m_sprite, *this);
  }

  void IconWidget::setAnchor(gf::Anchor anchor)
  {
    setOriginFromAnchorAndBounds(anchor, getLocalBounds());
  }

  void IconWidget::updateGeometry()
  {
    m_sprite.updateGeometry(m_vertices);

    auto changeColor = [this](gf::Color4f color) {
      for (auto& vertex : m_vertices) {
        vertex.color = color;
      }
    };

    switch(getState()) {
      case gf::WidgetState::Disabled:
        changeColor(m_disabledColor);
        break;
      case gf::WidgetState::Default:
        changeColor(m_defaultColor);
        break;
      case gf::WidgetState::Selected:
        changeColor(m_selectedColor);
        break;
    }
  }

  void IconWidget::onStateChanged()
  {
    updateGeometry();
  }

}
