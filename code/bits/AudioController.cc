#include "AudioController.h"

#include <gf/Log.h>

#include "GameHub.h"

namespace {
  constexpr float FadeOutTime = 2.5f;
  constexpr float DefaultVolume = 50.0f;
}

namespace mm {

  AudioController::AudioController(GameHub& game)
  : m_theaterAmbianceMusic(game.audioResources.getMusic("sounds/theater-ambiance.wav"))
  , m_broadcastMovieSoundBuffer(game.audioResources.getSound("sounds/broadcast-sfx.wav"))
  {
    m_broadcastMovieSound.setBuffer(m_broadcastMovieSoundBuffer);
    m_broadcastMovieSound.setLoop(false);
  }

  void AudioController::update(gf::Time time) {
    if (m_fadeout) {
      m_elapsedTime += time;
      if (m_elapsedTime.asSeconds() >= FadeOutTime) {
        m_theaterAmbianceMusic.stop();
      } else {
        float progress = m_elapsedTime.asSeconds() / FadeOutTime;
        m_theaterAmbianceMusic.setVolume(DefaultVolume - (DefaultVolume * progress));
      }
    }
  }

  void AudioController::startTheaterAmbiance() {
    m_theaterAmbianceMusic.setVolume(DefaultVolume);
    m_theaterAmbianceMusic.play();
    m_fadeout = false;
    m_elapsedTime = gf::Time::Zero;
  }

  void AudioController::stopTheaterAmbiance() {
    m_fadeout = true;
  }

  void AudioController::playBroadcastSfx() {
    m_broadcastMovieSound.play();
  }

}
