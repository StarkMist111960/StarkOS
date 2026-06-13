section .multiboot
align 4

dd 0x1BADB002
dd 0x00
dd - (0x1BADB002 + 0x00)

global start
extern kernel_main

section .text
bits 32

start:
        call kernel_main

hang:
        jmp hang
