#!/bin/bash

nasm -f elf64 loop_x86.asm -o inout_x86.o
gcc -e main inout_x86.o -o inout_x86
./inout_x86
rm inout_x86
rm inout_x86.o

