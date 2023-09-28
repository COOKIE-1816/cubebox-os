.section .text

.set VGA_MISC_WRITE		3C2h

.set VGA_SEQ_INDEX		3C4h
.set VGA_SEQ_DATA 		3C5h

.set VGA_CRTC_INDEX 	3D4h
.set VGA_CRTC_DATA		3D5h
.set VGA_INSTAT_READ	3DAh

.set NUM_SEQ_REGS		5
.set NUM_CRTC_REGS		25

.global vga_90x60
.type vga_90x60, @function
vga_90x60:
	mov %ax, 0003h
	int 10h

	mov %ax, 1112h
	xor %bl, %bl
	int 10h

	mov %si, $regs_90x60
	call write_regs

	mov %ax, 0040h
	mov %ds, %ax
	mov %es, %ax

	mov word [004Ah], 90
	mov word [004Ch], 90 * 60 * 2

	mov %cx, 8
	mov %di, 0050h
	xor %ax, %ax
	rep stosw

	mov word [0060h], 0607h

	mov byte [0084h], 59
	mov byte [0085h], 8
	
write_regs:
	push %si
	push %dx
	push %cx
	push %ax
	
	cld

	mov %dx, 	$VGA_MISC_WRITE
	lodsb
	out %dx, 	%al

	mov %cx, 	$NUM_SEQ_REGS
	mov %ah, 	0
	
write_seq:
	mov %dx,	$VGA_SEQ_INDEX
	mov %al,	%ah
	out %dx, 	%al

	mov %dx, 	$VGA_SEQ_DATA
	lodsb
	out %dx, 	%al

	inc %ah
	loop write_seq

	mov %dx, 	$VGA_CRTC_INDEX
	mov %al, 	17
	out %dx, 	%al

	mov %dx,	$VGA_CRTC_DATA
	in  %al, 	%dx
	and %al,	7Fh
	out %dx,	%al

	mov %dx,	$VGA_CRTC_INDEX
	mov %al,	3
	out %dx,	%al

	mov %dx,	$VGA_CRTC_DATA
	in  %al,	%dx
	or  %al,	80h
	out %dx,	%al

	mov %al,	[%si + 17]
	and %al,	7Fh
	
	mov [%si+17], %al

	mov %al,	[%si + 3]
	or  %al,	80h
	
	mov [%si + 3],%al

	mov %cx,	$NUM_CRTC_REGS
	mov %ah,	0
	
write_crtc:
	mov %dx,	$VGA_CRTC_INDEX
	mov %al,	%ah
	out %dx,	%al

	mov %dx,	$VGA_CRTC_DATA
	lodsb
	out %dx,	%al

	inc %ah
	loop write_crtc
	
	pop %ax
	pop %cx
	pop %dx
	pop %si
	
	ret

regs_90x60:
	# MISC
	db 0E7h
	
	# SEQuencer
	db 03h, 01h, 03h, 00h, 02h
	
	# CRTC
	db  6Bh, 59h,  5Ah, 82h, 60h,  8Dh, 0Bh,  3Eh,
	db  00h, 47h,  06h, 07h, 00h,  00h, 00h,  00h,
	db 0EAh, 0Ch, 0DFh, 2Dh, 08h, 0E8h, 05h, 0A3h,
	db 0FFh
