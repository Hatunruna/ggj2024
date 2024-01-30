#!/bin/sh

DIRECTORY=data/raw/i18n

xgettext --default-domain=MidnightMovies --output=${DIRECTORY}/MidnightMovies.pot --language=C++ --keyword=_ --keyword=N_ --sort-by-file code/main.cc code/bits/*.cc
