.section .text
.global _start
.type _start, @function
_start:
    mov $stack_top, %esp

    call _init
    call _fini

    cli

    call kmain

	call asmpanic

#    	cli
# 	1:	hlt
#		jmp 1b

.size _start, . - _start