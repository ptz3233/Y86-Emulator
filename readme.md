# Y86 Emulator

Emulator written in C for the full Y86 instruction set.
Y86  is a functionally complete subeset of the larger and more complicated x86 instruction set.
It takes in a byte code file containing the opcodes for the Y86 machine instructions, builds an emulated memory image and executes the instructions.

More information on the y86 instruction set and its funcionality can be found here:
http://cs.slu.edu/~fritts/CSCI224_S12/schedule/chap4-intro-Y86.pdf

Note that my emulator also contains a MOVSBL (move byte to long with sign extension) and instructions for reading and writing to the command line. These instructions are not mentioned in the aforementioned article, however, they make my emulator functionally complete.

This repository also contains a Y86 dissasembler (y86dis) and a Y86 program I wrote that accepts an integer input and returns the square.