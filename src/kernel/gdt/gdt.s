.extern gp

.section .text
.global gdt_flush
.type gdt_flush, @function
gdt_flush:
	cli
	
    # lgdt (gp)
    mov %ax, 0x10
	
    mov %ds, %ax
    mov %es, %ax
    mov %fs, %ax
    mov %gs, %ax
    mov %ss, %ax
	
    jmp flush2
flush2:
    ret
