#!/bin/bash

# remember to build everything first with ./build_linux.sh

# get the directory this script is in so we can call it from anywhere and have the same path
DIR="$( dirname "${BASH_SOURCE[0]}" )"
echo ${DIR}

# then when we want to run it
export LD_LIBRARY_PATH=\$ORIGIN/lib/
${DIR}/a.out
