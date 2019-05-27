#!/bin/bash

nasm -f elf64 my_in.asm -o my_in.o
gcc -e main my_in.o -o my_in
./my_in

