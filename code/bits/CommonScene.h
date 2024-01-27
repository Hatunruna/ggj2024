#ifndef MM_COMMON_SCENE_H
#define MM_COMMON_SCENE_H

#include <gf/Scene.h>

namespace mm {

  struct GameHub;

  class CommonScene: public gf::Scene {
  public:
    CommonScene(GameHub& game);

  private:
    void doHandleActions(gf::Window& window) override;

  private:
    gf::Action m_fullscreenAction;
  };

}

#endif // MM_COMMON_SCENE_H
