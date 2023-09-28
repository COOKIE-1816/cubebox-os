.extern exception_handler

.section .text
.global isr_stub_table
isr_stub_table:
	.long 0x00, 0x00, 0x00, 0x00, 0x00
	.long 0x00, 0x00, 0x00, 0x00, 0x00
	.long 0x00, 0x00, 0x00, 0x00, 0x00
	.long 0x00, 0x00, 0x00, 0x00, 0x00
	.long 0x00, 0x00, 0x00, 0x00, 0x00
	.long 0x00, 0x00, 0x00, 0x00, 0x00
	.long 0x00, 0x00


isr_no_err_stub_0:
	call exception_handler
	ret
isr_no_err_stub_1:
	call exception_handler
	ret
isr_no_err_stub_2:
	call exception_handler
	ret
isr_no_err_stub_3:
	call exception_handler
	ret
isr_no_err_stub_4:
	call exception_handler
	ret
isr_no_err_stub_5:
	call exception_handler
	ret
isr_no_err_stub_6:
	call exception_handler
	ret
isr_no_err_stub_7:
	call exception_handler
	ret
isr_err_stub_8:
	call exception_handler
	ret
isr_no_err_stub_9:
	call exception_handler
	ret
isr_err_stub_10:
	call exception_handler
	ret
isr_err_stub_11:
	call exception_handler
	ret
isr_err_stub_12:
	call exception_handler
	ret
isr_err_stub_13:
	call exception_handler
	ret
isr_err_stub_14:
	call exception_handler
	ret
isr_no_err_stub_15:
	call exception_handler
	ret
isr_no_err_stub_16:
	call exception_handler
	ret
isr_err_stub_17:
	call exception_handler
	ret
isr_no_err_stub_18:
	call exception_handler
	ret
isr_no_err_stub_19:
	call exception_handler
	ret
isr_no_err_stub_20:
	call exception_handler
	ret
isr_no_err_stub_21:
	call exception_handler
	ret
isr_no_err_stub_22:
	call exception_handler
	ret
isr_no_err_stub_23:
	call exception_handler
	ret
isr_no_err_stub_24:
	call exception_handler
	ret
isr_no_err_stub_25:
	call exception_handler
	ret
isr_no_err_stub_26:
	call exception_handler
	ret
isr_no_err_stub_27:
	call exception_handler
	ret
isr_no_err_stub_28:
	call exception_handler
	ret
isr_no_err_stub_29:
	call exception_handler
	ret
isr_err_stub_30:
	call exception_handler
	ret
isr_no_err_stub_31:
	call exception_handler
	ret
