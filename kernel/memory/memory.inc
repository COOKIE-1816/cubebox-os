BiosGetMemorySize:
	int	0x12
	jc	.error
	test ax, ax
	je .error
	cmp	ah, 0x86
	je	.error
	cmp	ah, 0x80
	je	.error

	ret

.error:
	mov	ax, -1
	ret

BiosGetExtendedMemorySize:
	mov	ax, 0x88
	int	0x15
	jc .error
	test ax, ax
	je .error
	cmp	ah, 0x86
	je .error
	cmp	ah, 0x80
	je .error

	ret

.error:
	mov	ax, -1
	ret

BiosGetMemorySize64MB:
	push	ecx
	push	edx
	xor	ecx, ecx		;clear all registers. This is needed for testing later
	xor	edx, edx
	mov	ax, 0xe801
	int	0x15	
	jc	.error
	cmp	ah, 0x86		;unsupported function
	je	.error
	cmp	ah, 0x80		;invalid command
	je	.error
	jcxz	.use_ax			;bios may have stored it in ax,bx or cx,dx. test if cx is 0
	mov	ax, cx			;its not, so it should contain mem size; store it
	mov	bx, dx
 
.use_ax:
	pop	edx			;mem size is in ax and bx already, return it
	pop	ecx
	ret
 
.error:
	mov	ax, -1
	mov	bx, 0
	pop	edx
	pop	ecx
	ret