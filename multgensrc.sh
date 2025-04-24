#!/bin/bash

if [ "$#" -lt 1 ]; then
	echo "Usage: $0 <src/> <src1/> [src2/ ...]"
	exit 1
fi

SRCDIR="\$(SRCDIR)"
OUTPUT=""

for SEARCHDIR in $@; do
	OUTPUT+="${SEARCHDIR^^}\t=\t"
	FILES=$(find $SEARCHDIR -maxdepth 1 -type f -name "*.c*" | sort)
	for FILE in $FILES; do
		OUTPUT+="$SRCDIR/${FILE#$SEARCHDIR/} \\\\\n"
	done
	FILES=$(find $SEARCHDIR -mindepth 2 -type f -name "*.c*" | sort)
	for FILE in $FILES; do
		OUTPUT+="$SRCDIR/${FILE#$SEARCHDIR/} \\\\\n"
	done
	OUTPUT+="\n"
done

echo -e "${OUTPUT::-3}"
