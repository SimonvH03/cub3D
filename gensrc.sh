#!/bin/bash

SRCDIR="\$(SRCDIR)"
OUTPUT="SRC\t\t=\t$SRCDIR/main.c \\\\"

FILES=$(find src -mindepth 2 -type f -name "*.c" | sort)

for FILE in $FILES; do
    if [[ "$OUTPUT" == "SRC\t\t= " ]]; then
        OUTPUT+="$SRCDIR/${FILE#src/} \\\\"
    else
        OUTPUT+="\n\t\t\t$SRCDIR/${FILE#src/} \\\\"
    fi
done

echo -e "${OUTPUT::-3}"