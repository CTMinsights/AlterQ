#!/bin/bash

lex aLex.l
g++ aLex.cpp strucTest.cpp aLexxer.c -o aLex -lfl
./alex