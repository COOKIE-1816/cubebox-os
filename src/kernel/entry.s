.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start:
    mov $stack_top, %esp
    cli

/*
    lgdt ($gdt_descriptor)
    mov %eax, %cr0
    or %eax, 0x1
    mov cr0, %eax

    mov %ax, DATA_SEG
    mov %ds, %ax
    mov %ss, %ax
    mov %es, %ax
    mov %fs, %ax
    mov %gs, %ax

    mov %ebp, 0x90000
    mov %esp, %ebp
*/

    call _init

    call kmain

    call _fini

   	cli
 1:	hlt
	jmp 1b

.size _start, . - _start
