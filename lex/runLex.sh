#!/bin/bash

lex aLex.l
g++ aLex.cpp ../structs/strucMain.cpp aLexxer.c -o aLex -lfl
./alex