#ifndef MM_ICON_WIDGET_H
#define MM_ICON_WIDGET_H

#include <gf/BasicSprite.h>
#include <gf/Texture.h>
#include <gf/Vertex.h>
#include <gf/Widget.h>

namespace mm {


  class IconWidget : public gf::Widget {
  public:
    /**
     * @brief Constructor with no texture
     */
    IconWidget() = default;

    IconWidget(const gf::Texture& texture, gf::Color4f defaultColor, gf::Color4f selectedColor, gf::Color4f disabledColor);

    void draw(gf::RenderTarget &target, const gf::RenderStates& states) override;

    bool contains(gf::Vector2f coords) override;

    gf::RectF getLocalBounds() const {
      return m_sprite.getLocalBounds();
    }

    void setAnchor(gf::Anchor anchor);

  private:
    void updateGeometry();
    void onStateChanged() override;

  private:
    gf::BasicSprite m_sprite;
    gf::Color4f m_defaultColor;
    gf::Color4f m_selectedColor;
    gf::Color4f m_disabledColor;
    gf::Vertex m_vertices[4];
  };


}

#endif // MM_ICON_WIDGET_H
