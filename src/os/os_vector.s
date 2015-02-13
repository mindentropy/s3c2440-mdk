.section .vector_reloc,"ax" //Apparent fix for missing section when objcopy is to have allocatable and executable flags-"ax"
//TODO: Understand the reason for the above flag.
.code 32

.globl exception_vectors

exception_vectors:
	b blink_led_test	//Reset vector
	b blink_led_test 	//Undefined instruction
	b blink_led_test 	//Software Interrupt
	b blink_led_test 	//Abort prefetch
	b blink_led_test	//Abort data
	b blink_led_test	//Reserved
	b blink_led_test	//IRQ
	b blink_led_test	//FIQ
.end
