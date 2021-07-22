PIO_PER equ 0x400E0E00
PIO_OER equ 0x400E0E10
PIO_SODR equ 0x400E0E30
PIO_CODR equ 0x400E0E34
PIO_IER equ 0x400E0E40
PIO_AIMDR equ 0x400E0EB4
PIO_IFDR equ 0x400E0E24
PIO_PDSR equ 0x400E0E3C
PIO_ODSR equ 0x400E0E38
PIO_OWER equ 0x400E0EA0

zero equ 0x0000007E
one equ 0x0000000C
two equ 0x000000B6
three equ 0x0000009E
four equ 0x000000CC
five equ 0x000000DA
six equ 0x000000FA
seven equ 0x0000000E
eight equ 0x000000FE
nine equ 0x000000DE
	
	area myCode, code, readonly
	export __main
	entry
	
__main
	ldr r6, =0x0000001
	mov r3, #7
	mov r7, #0
	mov r8, #0
	mov r9, #1
	ldr r1, =0x00000040
	bl enable_pio
	

loop
			ldr r5, =PIO_PDSR
			ldr r4, [r5]
			and r4, r4, r6
			cmp r4, #1
			movne r9, #1 
			bne loop
			cmp r9, #1
			moveq r9, #0
			moveq r7, #0
			moveq r8, #0
			bl delay
			ldr r5, =PIO_ODSR
			b input_on
			
input_on		
			;zero
			cmp r7, #0
			bne not_zero
			ldr r4, =zero
			b second_segment
			;one
not_zero	cmp r7, #1
			bne not_one
			ldr r4, =one
			b second_segment
			;two
not_one		cmp r7, #2
			bne not_two
			ldr r4, =two
			b second_segment
			;three
not_two		cmp r7, #3
			bne not_three
			ldr r4, =three
			b second_segment
			;four
not_three	cmp r7, #4
			bne not_four
			ldr r4, =four
			b second_segment
			;five
not_four	cmp r7, #5
			bne not_five
			ldr r4, =five
			b second_segment
			;six
not_five	cmp r7, #6
			bne not_six
			ldr r4, =six
			b second_segment
			;seven
not_six		cmp r7, #7
			bne not_seven
			ldr r4, =seven
			str r4, [r5]
			b second_segment
			;eight
not_seven	cmp r7, #8
			bne not_eight
			ldr r4, =eight
			b second_segment
			;nine
not_eight	cmp r7, #9
			ldr r4, =nine
			b second_segment

second_segment
			;zero
			cmp r8, #0
			bne not_zero2
			ldr r2, =zero
			b next
			;one
not_zero2	cmp r8, #1
			bne not_one2
			ldr r2, =one
			b next
			;two
not_one2	cmp r8, #2
			bne not_two2
			ldr r2, =two
			b next
			;three
not_two2	cmp r8, #3
			bne not_three2
			ldr r2, =three
			b next
			;four
not_three2	cmp r8, #4
			bne not_four2
			ldr r2, =four
			b next
			;five
not_four2	cmp r8, #5
			bne not_five2
			ldr r2, =five
			b next
			;six
not_five2	cmp r8, #6
			bne not_six2
			ldr r2, =six
			b next
			;seven
not_six2	cmp r8, #7
			bne not_seven2
			ldr r2, =seven
			b next
			;eight
not_seven2	cmp r8, #8
			bne not_eight2
			ldr r2, =eight
			b next
			;nine
not_eight2	cmp r8, #9
			ldr r2, =nine
			b next	
			
next		
			mov r2, r2, LSL r3
			orr r4, r4, r2
			str r4, [r5]
			add r7, r7, #1
			cmp r7, #10
			addeq r8, r8, #1
			moveq r7, #0
			
			b loop

enable_pio
			ldr r4, =0x7FFE
			
			ldr r5, =PIO_PER
			str r4, [r5]
			
			ldr r5, =PIO_OER
			str r4, [r5]
			
			ldr r5, =PIO_OWER
			str r4, [r5]

			mov r4, #2_1
			
			ldr r5, =PIO_IFDR
			str r4, [r5] 
			
			bx lr
	
delay
			mov r4, #0
			ldr r5, =0x0000A000
			
	
delay_loop
			add r4, r4, #1
			
			cmp r4, r5
			bne delay_loop
			bx lr
			
			end