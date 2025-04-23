#!/bin/bash

# if [ "$#" -lt 1 ]; then
# 	echo "Usage: $0 <src/> <src1/> [src2/ ...]"
# 	exit 1
# fi

# SRCDIR="\$(SRCDIR)"
# OUTPUT=""

# for SEARCHDIR in $@; do
# 	FILES=$(find $SEARCHDIR -type f -name "*.c*" | sort)

# 	for FILE in $FILES; do
# 		OUTPUT+="\n$SRCDIR/${FILE#$SEARCHDIR/} \\\\"
# 	done
# 	OUTPUT+="\n"
# done

# echo -e "${OUTPUT::-3}"