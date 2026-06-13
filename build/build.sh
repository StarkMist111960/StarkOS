#!/bin/bash

echo 'use of this requires WSL or a linux distribution that supports APT'

read -p 'do you wish to continue (y,n)?'ANS

if [$ANS -eq 'y']; then

  cd ~/

  echo 'recieving a clone of the repo...'

  git clone --depth 1 https://github.com/StarkMist111960/StarkOS.git

  cd ~/StarkOS/main
  
  echo 'installing needed things and stuff...'

  sudo apt update && upgrade

  sleep 2
  
  sudo apt install build-essential nasm grub-pc-bin xorriso mtools qemu-system-x86

  echo 'installed needed things successfully, continuing to build...'

  mkdir output
  nasm -f elf32 boot/boot.asm -o output/boot.o
  gcc -m32 -ffreestanding -c kernel/kernel.c -o output/kernel.o
  ld -m elf_i386 -T linker.ld -o kernel/kernel.bin output/boot.o output/kernel.o
  cp kernel/kernel.bin iso/boot/

  grub-mkrescue -o StarkOS.iso iso

  echo 'run success! Things ran and built flawlessly, use this qemu command to test in a VM (or flash to a usb idc): qemu-system-i386 -cdrom StarkOS.iso'

else
  echo 'cancelled, now exiting'

  sleep 3

  exit 1
fi
