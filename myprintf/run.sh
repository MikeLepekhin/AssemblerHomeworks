#!/bin/bash

nasm -f elf64 myprintf.asm -o myprintf.o
gcc hello.c myprintf.o -o myprintf
./myprintf
