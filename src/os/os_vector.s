.section .vector_reloc,"ax" //Apparent fix for missing section when objcopy is to have allocatable and executable flags-"ax"
//TODO: Understand the reason for the above flag.
.code 32

.globl exception_vectors

exception_vectors:
	ldr pc,=do_handle_reset		//Reset vector
	ldr pc,=do_handle_undef 	//Undefined instruction
	ldr pc,=do_handle_swi 		//Software Interrupt
	ldr pc,=do_handle_pabt 		//Abort prefetch
	ldr pc,=do_handle_dabt		//Abort data
	ldr pc,=do_handle_reserved	//Reserved
	ldr pc,=do_handle_irq		//IRQ
	ldr pc,=do_handle_fiq		//FIQ
.end
