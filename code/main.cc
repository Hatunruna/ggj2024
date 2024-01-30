#include <cstdlib>

#include <boost/locale.hpp>

#include <gf/Log.h>

#include "bits/GameHub.h"

#include "config.h"

int main() {
  // locale

  boost::locale::generator localeGenerator;
  localeGenerator.add_messages_path(GAME_LOCALEDIR);
  localeGenerator.add_messages_domain("MidnightMovies");
  std::locale::global(localeGenerator(""));
  gf::Log::info("Locale is: %s\n", std::locale("").name().c_str());

  mm::GameHub hub;
  hub.run();

  return EXIT_SUCCESS;
}
