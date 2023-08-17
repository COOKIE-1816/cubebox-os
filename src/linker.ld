 
ENTRY(_start)

SECTIONS
{
	. = 1M;
 
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}

.init_array :
{
    crti.o(.init_array)
    KEEP (*(SORT(EXCLUDE_FILE(crti.o crtn.o) .init_array.*)))
    KEEP (*(EXCLUDE_FILE(crti.o crtn.o) .init_array))
    crtn.o(.init_array)
}

.fini_array :
{
    crti.o(.fini_array)
    KEEP (*(SORT(EXCLUDE_FILE(crti.o crtn.o) .fini_array.*)))
    KEEP (*(EXCLUDE_FILE(crti.o crtn.o) .fini_array))
    crtn.o(.fini_array)
}

}