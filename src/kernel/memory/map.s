struc memory_mapEntry
    .baseAddress resq 1
    .length      resq 1
    .type        resd 1
    .acpi_null   resd 1
endstruc

memory_getMap:
    pushad

    xor ebx, ebx
    xor bp, bo

    mov edx, 'PAMS'
    mov eax, 0xE820
    mov ecx, 24

    int 0x15
    jc .error

    cmp eax, 'PAMS'
    jne .error

    test ebx, ebx
    je .error

    jmp .start
.nextEntry:
    mov edx, 'PAMS'
    mov ecx, 24
    mov eax, 0xE820

    int 0x15
.start:
    jcxz .skipEntry
.notext:
    mov ecx, [es:di + memory_mapEntry.length]
    test ecx, ecx
    jne short .goodEntry

    mov ecx, [es:di + memory_mapEntry.length + 4]
    jecxz .skipEntry
.goodEntry:
    inc bp
    add di, 24
.skipEntry:
    cmp ebx, 0x00
    jne .nextEntry
    jmp .done
.error:
    stc
.done:
    popad
    ret
