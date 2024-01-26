#include "MovieManager.h"

namespace mm {

  void MovieManager::update(gf::Time time) {
    switch (m_state)
    {
    case State::NoMovie:
      m_state = State::ArrivingMovie;
      m_currentMovie.position = gf::Vector2f
      break;
    }
  }

  void MovieManager::render(gf::RenderTarget& target, const gf::RenderStates& states) {

  }

}
