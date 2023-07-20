gdtr    DW 0
        DD 0
 
.section .setGdt
.global _setGdt
.type _setGdt, @function
_setGdt:
    MOV   AX, [esp + 4]
    MOV   [gdtr], AX
    MOV   EAX, [ESP + 8]
    MOV   [gdtr + 2], EAX
    LGDT  [gdtr]
    RET

gdt_start:
    
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1   ; Limit field (size of GDT - 1)
    dd gdt_start                 ; Base address of GDT

.section reloadSegments
.global _reloadSegments
.type _reloadSegments, @function
_reloadSegments:
    JMP   0x08:.reload_CS
.reload_CS:
    MOV   AX, 0x10
    MOV   DS, AX
    MOV   ES, AX
    MOV   FS, AX
    MOV   GS, AX
    MOV   SS, AX

    RET