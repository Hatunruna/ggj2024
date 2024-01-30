#!/bin/sh

DIRECTORY=data/raw/i18n
LANGUAGES=fr

for LANG in $LANGUAGES
do
  echo "Merging for ${LANG}..."
  msgmerge --update --backup=none "${DIRECTORY}/${LANG}.po" "${DIRECTORY}/MidnightMovies.pot"
done
