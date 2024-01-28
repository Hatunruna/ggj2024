#ifndef MM_AUDIO_CONTROLLER_H
#define MM_AUDIO_CONTROLLER_H

#include <SFML/Audio.hpp>

#include <gf/Entity.h>

namespace mm {

  struct GameHub;

  class AudioController: public gf::Entity {
  public:
    AudioController(GameHub& game);

    virtual void update(gf::Time time) override;

    void startTheaterAmbiance();
    void stopTheaterAmbiance();

    void playBroadcastSfx();

  private:
    sf::Music& m_theaterAmbianceMusic;
    sf::SoundBuffer& m_broadcastMovieSoundBuffer;
    sf::Sound m_broadcastMovieSound;

    bool m_fadeout = false;
    gf::Time m_elapsedTime;
  };

}

#endif // MM_AUDIO_CONTROLLER_H
