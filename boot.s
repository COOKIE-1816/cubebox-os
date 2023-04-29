MBALIGN		equ 1 << 0
MEMINFO		equ 1 << 1
MBFLAGS		equ MBALIGN | MEMINFO
MAGIC		equ 0x1badb002

section .multiboot
align 4
	dd MAGIC
	dd MBFLAGS
	dd CHECKSUM

struc multiboot_info
	.flags		resd	1	; required
	.memoryLo	resd	1	; memory size. Present if flags[0] is set
	.memoryHi	resd	1
	.bootDevice	resd	1	; boot device. Present if flags[1] is set
	.cmdLine	resd	1	; kernel command line. Present if flags[2] is set
	.mods_count	resd	1	; number of modules loaded along with kernel. present if flags[3] is set
	.mods_addr	resd	1
	.syms0		resd	1	; symbol table info. present if flags[4] or flags[5] is set
	.syms1		resd	1
	.syms2		resd	1
	.mmap_length	resd	1	; memory map. Present if flags[6] is set
	.mmap_addr	resd	1
	.drives_length	resd	1	; phys address of first drive structure. present if flags[7] is set
	.drives_addr	resd	1
	.config_table	resd	1	; ROM configuation table. present if flags[8] is set
	.bootloader_name resd	1	; Bootloader name. present if flags[9] is set
	.apm_table	resd	1	; advanced power management (apm) table. present if flags[10] is set
	.vbe_control_info resd	1	; video bios extension (vbe). present if flags[11] is set
	.vbe_mode_info	resd	1
	.vbe_mode	resw	1
	.vbe_interface_seg resw	1
	.vbe_interface_off resw	1
	.vbe_interface_len resw	1
endstruc

section .bss
align 16
stack_bottom:
resb 16384
stack_top:
section .text
global _start:function (_start.end - _start)
_start:
	mov esp, stack_top

    mov	eax, 0x2BADB002
	mov	ebx, 0
	mov	edx, [ImageSize]

    push dword boot_info

	extern kmain
	call kmain

	cli
.hang:	hlt
		jmp .hang 
.end

gdtr DW 0 ; For limit storage
     DD 0 ; For base storage
 
setGdt:
   MOV   AX, [esp + 4]
   MOV   [gdtr], AX
   MOV   EAX, [ESP + 8]
   ADD   EAX, [ESP + 12]
   MOV   [gdtr + 2], EAX
   LGDT  [gdtr]
   RET

reloadSegments:
   JMP   0x08:.reload_CS
.reload_CS:
   MOV   AX, 0x10
   MOV   DS, AX
   MOV   ES, AX
   MOV   FS, AX
   MOV   GS, AX
   MOV   SS, AX
   RET

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31


isr0:
    push byte 0
    push byte 0
    jmp isr_common_stub
    
isr1:
    push byte 0
    push byte 1
    jmp isr_common_stub
isr2:
    push byte 0
    push byte 1
    jmp isr_common_stub
isr3:
    push byte 0
    push byte 1
    jmp isr_common_stub
isr4:
    push byte 0
    push byte 1
    jmp isr_common_stub
isr5:
    push byte 0
    push byte 1
    jmp isr_common_stub
isr6:
    push byte 0
    push byte 1
    jmp isr_common_stub
isr7:
    push byte 0
    push byte 1
    jmp isr_common_stub
isr8:
    push byte 0
    push byte 1
    jmp isr_common_stub
isr9:
    push byte 0
    push byte 1
    jmp isr_common_stub
isr10:
    push byte 0
    push byte 1
    jmp isr_common_stub
isr11:
    push byte 0
    push byte 1
    jmp isr_common_stub
isr12:
    push byte 12
    jmp isr_common_stub
isr13:
    push byte 12
    jmp isr_common_stub
isr14:
    push byte 12
    jmp isr_common_stub
isr15:
    push byte 12
    jmp isr_common_stub
isr16:
    push byte 12
    jmp isr_common_stub
isr17:
    push byte 12
    jmp isr_common_stub
isr18:
    push byte 12
    jmp isr_common_stub
isr19:
    push byte 12
    jmp isr_common_stub
isr20:
    push byte 12
    jmp isr_common_stub
isr21:
    push byte 12
    jmp isr_common_stub
isr22:
    push byte 12
    jmp isr_common_stub
isr23:
    push byte 12
    jmp isr_common_stub
isr24:
    push byte 12
    jmp isr_common_stub
isr25:
    push byte 12
    jmp isr_common_stub
isr26:
    push byte 12
    jmp isr_common_stub
isr27:
    push byte 12
    jmp isr_common_stub
isr28:
    push byte 12
    jmp isr_common_stub
isr29:
    push byte 12
    jmp isr_common_stub
isr30:
    push byte 12
    jmp isr_common_stub
isr31:
    push byte 0
    push byte 31
    jmp isr_common_stub

[extern isr_handler]
isr_common_stub:
    pusha

    mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp

    call isr_handler
 
    pop eax

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa

    add esp, 8


    iret
    
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

irq0:
    push byte 0
    push byte 32
    jmp irq_common_stub
irq1:
    push byte 0
    push byte 32
    jmp irq_common_stub
irq2:
    push byte 0
    push byte 32
    jmp irq_common_stub
irq3:
    push byte 0
    push byte 32
    jmp irq_common_stub
irq4:
    push byte 0
    push byte 32
    jmp irq_common_stub
irq5:
    push byte 0
    push byte 32
    jmp irq_common_stub
irq6:
    push byte 0
    push byte 32
    jmp irq_common_stub
irq7:
    push byte 0
    push byte 32
    jmp irq_common_stub
irq8:
    push byte 0
    push byte 32
    jmp irq_common_stub
irq9:
    push byte 0
    push byte 32
    jmp irq_common_stub
irq10:
    push byte 0
    push byte 32
    jmp irq_common_stub
irq11:
    push byte 0
    push byte 32
    jmp irq_common_stub
irq12:
    push byte 0
    push byte 32
    jmp irq_common_stub
irq13:
    push byte 0
    push byte 32
    jmp irq_common_stub
irq14:
    push byte 0
    push byte 32
    jmp irq_common_stub
irq15:
    push byte 15
    push byte 47
    jmp irq_common_stub
