#!/bin/sh

DIRECTORY=data/raw/i18n
LANGUAGES=fr

for LANG in $LANGUAGES
do
  echo "Compiling for ${LANG}..."
  msgfmt -o "${DIRECTORY}/${LANG}.gmo" "${DIRECTORY}/${LANG}.po"
  mkdir -p "${DIRECTORY}/${LANG}/LC_MESSAGES"
  cp -f "${DIRECTORY}/${LANG}.gmo" "${DIRECTORY}/${LANG}/LC_MESSAGES/MidnightMovies.mo"
done
