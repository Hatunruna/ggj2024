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
magick montage -background transparent -tile 2x2 -geometry 1168x2160 win/scene1-seq1/* ../MidnightMovies/images/animation/good-ending/good-ending-scene1-seq1.png
magick montage -background transparent -tile 2x2 -geometry 1156x2160 win/scene2-seq1/* ../MidnightMovies/images/animation/good-ending/good-ending-scene2-seq1.png
magick montage -background transparent -tile 2x2 -geometry 1156x2160 win/scene2-seq2/* ../MidnightMovies/images/animation/good-ending/good-ending-scene2-seq2.png
magick montage -background transparent -tile 2x2 -geometry 1156x2160 win/scene2-seq3/* ../MidnightMovies/images/animation/good-ending/good-ending-scene2-seq3.png
