#ifndef MM_MOVIE_MANAGER_H
#define MM_MOVIE_MANAGER_H

#include <gf/Entity.h>
#include <gf/Vector.h>

namespace mm {

  struct Movie {
    gf::Vector2f position;
  };

  class MovieManager: public gf::Entity {
  public:
    virtual void update(gf::Time time) override;
    virtual void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    enum class State {
      NoMovie,
      ArrivingMovie,
      WaitingMovie,
    };

  private:
    State m_state = State::NoMovie;
    gf::Time m_elapsedTime;
    Movie m_currentMovie;
  };

}

#endif // MM_MOVIE_MANAGER_H
