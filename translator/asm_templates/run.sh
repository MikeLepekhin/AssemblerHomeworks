#!/bin/bash

nasm -f elf64 header.asm -o header.o
gcc -e main header.o -o header
./header
rm header
rm header.o

