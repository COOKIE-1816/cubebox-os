#include "kernel/kernel.h"
#include "kernel/tty/tty.h"
#include "kernel/gdt/gdt.h"

#if defined(__linux__)
	#error "Cross-compiler required"
#endif
#if !defined(__i386__)
	#error "Invalid target"
#endif

void kernel_main(multiboot_info* bootInfo) {
	tty_init();

	println("CubeBox, kernel (core) version 1.0.05.00a");
	println("   Copyright (C) Vaclav Hajsman 2023 - All rights reserved.");
	println("   http://czechcookie.euweb.com/cb");
	println("   https://github.com/COOKIE-1816/cubebox\n\n");

	gdt_init();
}