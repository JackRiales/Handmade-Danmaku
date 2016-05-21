#!/bin/bash

# Directory of the output file here
DIR="Build"

# Compile type (Debug/Release)
TYPE="Debug"

# Name of the output file here
NAME="HandmadeDanmaku.out"

# Final output string
OUTPUT="$DIR/$TYPE/$NAME"

# Library linkages here
echo "Setting up linkage variables..."
LIBS="-lX11 -lGL -lglut -lGLU"

# Create directory if it doesnt exist
if [ ! -d "$DIR$TYPE" ]; then
    echo "Creating directory $DIR/$TYPE because it did not exist..."
    mkdir -p "$DIR/$TYPE"
fi

# Compilation
echo "Compiling...";
g++ -g -Wno-write-strings ./src/linux_hmdanmaku.cpp -o $OUTPUT $LIBS
