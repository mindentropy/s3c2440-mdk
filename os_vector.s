.section exception_vectors_reloc
.code 32

.globl exception_vectors

exception_vectors:

/*	ldr pc,[pc,#0x30000000] //Reset vector
	ldr pc,[pc,#0x30000000] //Undefined instruction
	ldr pc,[pc,#0x30000000] //Software Interrupt
	ldr pc,[pc,#0x30000000] //Abort prefetch
	ldr pc,[pc,#0x30000000] //Abort data
	ldr pc,[pc,#0x30000000] //Reserved
	ldr pc,[pc,#0x30000000] //IRQ
	ldr pc,[pc,#0x30000000] //FIQ

*/
.end
	
