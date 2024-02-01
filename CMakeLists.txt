cmake_minimum_required(VERSION 3.10)

set(GAME MidnightMovies)

project(${GAME}
  VERSION 0.1.0
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")

include(GNUInstallDirs)

find_package(gf REQUIRED COMPONENTS graphics)
find_package(SFML REQUIRED COMPONENTS audio)
find_package(Boost REQUIRED COMPONENTS locale)

if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif ()

set(GAME_DATADIR "${CMAKE_INSTALL_PREFIX}/share/games/${GAME}" CACHE STRING "Game Data Dir")
set(GAME_LOCALEDIR "${CMAKE_INSTALL_FULL_LOCALEDIR}" CACHE STRING "Game Locale Dir")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/code/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h @ONLY)

set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")

add_subdirectory(vendor/json)

add_executable(${GAME}
  code/main.cc
  code/bits/AudioController.cc
  code/bits/AudioManager.cc
  code/bits/CommonScene.cc
  code/bits/ConstraintListScene.cc
  code/bits/DebriefEntity.cc
  code/bits/DebriefScene.cc
  code/bits/FeedbackEntity.cc
  code/bits/GameData.cc
  code/bits/GameHub.cc
  code/bits/GameOverEntity.cc
  code/bits/GameOverScene.cc
  code/bits/GameState.cc
  code/bits/IconWidget.cc
  code/bits/MovieData.cc
  code/bits/MovieManager.cc
  code/bits/RequirementsEntity.cc
  code/bits/StartScene.cc
  code/bits/TitleEntity.cc
  code/bits/TheaterScene.cc
  code/bits/TheaterBackgroundEntity.cc
)

target_link_libraries(${GAME} PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(${GAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/code
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${GAME}
  PRIVATE
    gf::graphics
    sfml-audio
    Boost::locale
)

if (WIN32)
  add_custom_command(TARGET ${GAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${GAME}> $<TARGET_FILE_DIR:${GAME}>
    COMMAND_EXPAND_LISTS
  )

  install(
    FILES
      $<TARGET_FILE_DIR:${GAME}>/SDL2d.dll
      $<TARGET_FILE_DIR:${GAME}>/boost_locale-vc143-mt-x64-1_83.dll
      $<TARGET_FILE_DIR:${GAME}>/brotlicommon.dll
      $<TARGET_FILE_DIR:${GAME}>/brotlidec.dll
      $<TARGET_FILE_DIR:${GAME}>/bz2d.dll
      $<TARGET_FILE_DIR:${GAME}>/freetyped.dll
      $<TARGET_FILE_DIR:${GAME}>/gf0.dll
      $<TARGET_FILE_DIR:${GAME}>/gfcore0.dll
      $<TARGET_FILE_DIR:${GAME}>/libpng16d.dll
      $<TARGET_FILE_DIR:${GAME}>/pugixml.dll
      $<TARGET_FILE_DIR:${GAME}>/zlibd1.dll
      $<TARGET_FILE_DIR:${GAME}>/FLAC.dll
      $<TARGET_FILE_DIR:${GAME}>/ogg.dll
      $<TARGET_FILE_DIR:${GAME}>/OpenAL32.dll
      $<TARGET_FILE_DIR:${GAME}>/sfml-audio-d-2.dll
      $<TARGET_FILE_DIR:${GAME}>/sfml-system-d-2.dll
      $<TARGET_FILE_DIR:${GAME}>/vorbis.dll
      $<TARGET_FILE_DIR:${GAME}>/vorbisenc.dll
      $<TARGET_FILE_DIR:${GAME}>/vorbisfile.dll
      $<TARGET_FILE_DIR:${GAME}>/${GAME}.pdb
    DESTINATION .
    CONFIGURATIONS Debug
  )

  install(
    FILES
      $<TARGET_FILE_DIR:${GAME}>/SDL2.dll
      $<TARGET_FILE_DIR:${GAME}>/boost_locale-vc143-mt-x64-1_83.dll
      $<TARGET_FILE_DIR:${GAME}>/brotlicommon.dll
      $<TARGET_FILE_DIR:${GAME}>/brotlidec.dll
      $<TARGET_FILE_DIR:${GAME}>/bz2.dll
      $<TARGET_FILE_DIR:${GAME}>/freetype.dll
      $<TARGET_FILE_DIR:${GAME}>/gf0.dll
      $<TARGET_FILE_DIR:${GAME}>/gfcore0.dll
      $<TARGET_FILE_DIR:${GAME}>/libpng16.dll
      $<TARGET_FILE_DIR:${GAME}>/pugixml.dll
      $<TARGET_FILE_DIR:${GAME}>/zlib1.dll
      $<TARGET_FILE_DIR:${GAME}>/FLAC.dll
      $<TARGET_FILE_DIR:${GAME}>/ogg.dll
      $<TARGET_FILE_DIR:${GAME}>/OpenAL32.dll
      $<TARGET_FILE_DIR:${GAME}>/sfml-audio-2.dll
      $<TARGET_FILE_DIR:${GAME}>/sfml-system-2.dll
      $<TARGET_FILE_DIR:${GAME}>/vorbis.dll
      $<TARGET_FILE_DIR:${GAME}>/vorbisenc.dll
      $<TARGET_FILE_DIR:${GAME}>/vorbisfile.dll
    DESTINATION .
    CONFIGURATIONS Release
  )

  install(TARGETS ${GAME} DESTINATION .)
  install(FILES ${CMAKE_SOURCE_DIR}/README.md DESTINATION .)
else ()
  install(TARGETS ${GAME} RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
endif ()

if (WIN32)
  install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/data/${GAME}/"
    DESTINATION "./data/"
  )
else ()
  install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/data/${GAME}"
    DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/games"
  )
endif ()
# Package rules
if (WIN32)
  set(CPACK_GENERATOR "ZIP")
  include(CPack)
endif()
