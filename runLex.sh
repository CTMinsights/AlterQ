#!/bin/bash

cd lex
lex aLex.l
cd ../
make
./prog

