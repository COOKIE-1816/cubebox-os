section .text
global i86_keyboard_irq_asm

i86_keyboard_irq_asm:
    sti
    pop edi
    pop esi
    pop ebp
    pop ebx
    pop edx
    pop ecx
    pop eax
    ret
