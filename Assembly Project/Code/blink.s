PIO_PER equ 0x400E0E00
PIO_OER equ 0x400E0E10
PIO_SODR equ 0x400E0E30
PIO_CODR equ 0x400E0E34
	
	area myCode, code, readonly
	export __main
	entry
	
__main
	bl enable_pio
	

loop
	bl led_on
	bl delay
	bl led_off
	bl delay
	b loop


enable_pio
	mov r4, #2_1
	
	ldr r5, =PIO_PER
	str r4, [r5]
	
	ldr r5, =PIO_OER
	str r4, [r5]
	
	bx lr


led_on
	mov r4, #2_1
	ldr r5, =PIO_SODR
	str r4, [r5]
	
	bx lr
	

led_off
	mov r4, #2_1
	ldr r5, =PIO_CODR
	str r4, [r5]
	
	bx lr
	
delay
	mov r4, #0
	ldr r5, =0x000A0000
	
	
delay_loop
	add r4, r4, #1
	
	cmp r4, r5
	bne delay_loop
	bx lr
	
	end





