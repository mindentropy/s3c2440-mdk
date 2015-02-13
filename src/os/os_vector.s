.section .vector_reloc,"ax" //Apparent fix for missing section when objcopy is to have allocatable and executable flags-"ax"
//TODO: Understand the reason for the above flag.
.code 32

.globl exception_vectors

exception_vectors:
	ldr pc,=blink_led_test	//Reset vector
	ldr pc,=blink_led_test 	//Undefined instruction
	ldr pc,=blink_led_test 	//Software Interrupt
	ldr pc,=blink_led_test 	//Abort prefetch
	ldr pc,=blink_led_test	//Abort data
	ldr pc,=blink_led_test	//Reserved
	ldr pc,=blink_led_test	//IRQ
	ldr pc,=blink_led_test	//FIQ
.end
