#!/bin/bash

nasm -f elf64 test.nasm -o test.o
ld -o test test.o
