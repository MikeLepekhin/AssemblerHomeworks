#!/bin/bash

nasm -f elf64 my_out.asm -o my_out.o
ld -e main my_out.o -o my_out
./my_out
