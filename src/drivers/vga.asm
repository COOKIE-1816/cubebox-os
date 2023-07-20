section .text
global _vga_videoMode: function
_vga_videoMode:
    mov ah, 0x00
    mov al, 0x13 ; mode 13

    int 10h

section .text
global _vga_textMode: function
_vga_textMode:
    mov ah, 0x00
    mov al, 0x03

    int 10h

section .text
global _vga_init: function
_vga_init:
    call _vga_videoMode