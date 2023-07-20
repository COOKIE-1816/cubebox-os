bits 32

.extern _vga_init

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

a20_enable:
	cli

	in al, 0x92
	or al, 0x02

	out 0x92, al

	sti
	ret

protectedMode_enable:
	mov eax, cr0
	or  eax, 0x01

	mov cr0, eax

protectedMode:
	call kernel_main

	cli
	call kcrash

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

	call protectedMode_enable 	# enable protected mode
	call _init					# global constructors
	call a20_enable				# enable A20

	lgdt [gdt_descriptor]
	lidt [idt_descriptor]

	jmp 0x08:protectedMode

1:	hlt
	jmp 1b

.size _start, . - _start


