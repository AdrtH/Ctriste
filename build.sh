#!/bin/bash


gcc -Wall -Wextra test.c -o test -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
gcc -Wall -Wextra main.c -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
