#!/usr/bin/bash

magick montage -background transparent -tile 4x1 -geometry 1239x2160 joie/* ../MidnightMovies/images/monster-happy-a.png
magick montage -background transparent -tile 4x1 -geometry 1239x2160 colere/* ../MidnightMovies/images/monster-angry-a.png
magick montage -background transparent -tile 4x1 -geometry 1239x2160 joie_soft/* ../MidnightMovies/images/monster-happy-b.png
magick montage -background transparent -tile 4x1 -geometry 1239x2160 colere_soft/* ../MidnightMovies/images/monster-angry-b.png
