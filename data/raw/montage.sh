#!/usr/bin/bash

magick montage -background transparent -tile 4x1 -geometry 1239x2160 joie/* ../MidnightMovies/images/monster-happy-a.png
magick montage -background transparent -tile 4x1 -geometry 1239x2160 colere/* ../MidnightMovies/images/monster-angry-a.png
magick montage -background transparent -tile 4x1 -geometry 1239x2160 joie_soft/* ../MidnightMovies/images/monster-happy-b.png
magick montage -background transparent -tile 4x1 -geometry 1239x2160 colere_soft/* ../MidnightMovies/images/monster-angry-b.png
magick montage -background transparent -tile 4x1 -geometry 1239x2160 light/* ../MidnightMovies/images/projector.png
magick montage -background transparent -tile 2x2 -geometry 1201x2160 gameover/00_start/* ../MidnightMovies/images/animation/bad-ending/bad-ending-scene1-start.png
magick montage -background transparent -tile 2x2 -geometry 1201x2160 gameover/01_middle/* ../MidnightMovies/images/animation/bad-ending/bad-ending-scene1-rumble-end.png
magick montage -background transparent -tile 2x2 -geometry 1757x2160 gameover/02_start_end/* ../MidnightMovies/images/animation/bad-ending/bad-ending-scene2-start.png
magick montage -background transparent -tile 2x2 -geometry 1757x2160 gameover/03_tremble_28_61/* ../MidnightMovies/images/animation/bad-ending/bad-ending-scene2-middle.png
magick montage -background transparent -tile 2x2 -geometry 1757x2160 gameover/04_start_end/* ../MidnightMovies/images/animation/bad-ending/bad-ending-scene2-end.png
