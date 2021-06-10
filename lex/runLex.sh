#!/bin/bash

lex aLex.l
g++ aLex.cpp ../structs/strucTest.cpp aLexxer.c -o aLex -lfl
./alex