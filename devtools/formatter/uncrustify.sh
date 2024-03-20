#!/usr/bin/env bash

# https://stackoverflow.com/a/246128
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $DIR
printf "Using working directory: $DIR\n"

UNCRUSTIFY=$(which uncrustify 2>/dev/null)
UNCRUSTIFY="${UNCRUSTIFY:-$DIR/uncrustify.exe}"
printf "Using Uncrustify at \"$UNCRUSTIFY\" ...\n"

find ../../ -type d -name '.pio' -prune -o -type f \( -name "*.hpp" -o -name "*.h" -o -name "*.cpp" -o -name "*.c" \) -print -exec $UNCRUSTIFY -c ./uncrustify.cfg --replace --no-backup {} +