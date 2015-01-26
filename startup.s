//[BITS 32]
//[global start]
//[extern _kernel_main] ; this is in the c file
//----- Multiboot Header Starts Here -----
// Multiboot header constant definition
.extern kernel_main

.equ MULTIBOOT_PAGE_ALIGN, 1<<0
.equ MULTIBOOT_MEMORY_INFO, 1<<1
.equ MULTIBOOT_HEADER_MAGIC, 0x1BADB002
.equ MULTIBOOT_HEADER_FLAGS, MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
.equ CHECKSUM, -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
// The Multiboot header
//.bits 32

.global start #for GRUB
start:
    jmp after_multiboot_magic
.align 4
.int MULTIBOOT_HEADER_MAGIC
.int MULTIBOOT_HEADER_FLAGS
.int CHECKSUM
// ----- Multiboot Header Ends Here -----

after_multiboot_magic:


call kernel_main
cli # stop interrupts
hlt # halt the CPU
