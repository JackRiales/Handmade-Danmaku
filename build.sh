#!/bin/bash

# Directory of the output file here
DIR="Build"

# Compile type (Debug/Release)
TYPE="Debug"

# Name of the output file here
NAME="HandmakeDanmaku.out"

# Final output string
OUTPUT="$DIR/$TYPE/$NAME"

# Library linkages here
echo "Setting up linkage variables..."
LIBS="-lX11"

# Create directory if it doesnt exist
if [ ! -d "$DIR$TYPE" ]; then
    mkdir -p "$DIR/$TYPE"
fi

# Compilation
echo "Compiling...";
g++ -Wno-write-strings ./src/linux_hmdanmaku.cpp -o $OUTPUT $LIBS
