#!/bin/bash

INC=inc
SRC=src
BUILD=build
OUT=sdlbsp

CC=gcc
CFLAGS="-I$INC -Wall -lSDL2 -lm -g"
SRCS="$(find $SRC/common/ $SRC/linux/ -name '*.c' -printf '%p ')"

echo "$CC $CFLAGS $SRCS -o $BUILD/$OUT"
$CC $CFLAGS $SRCS -o $BUILD/$OUT
