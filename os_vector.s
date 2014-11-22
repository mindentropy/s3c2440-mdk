.section exception_vectors_reloc
.code 32

.globl exception_vectors

exception_vectors:
	ldr pc,=#0x30000000 //Reset vector
	ldr pc,=#0x30000004 //Reset vector
	ldr pc,=#0x30000008 //Undefined instruction
	ldr pc,=#0x3000000C //Software Interrupt
	ldr pc,=#0x30000010 //Abort prefetch
	ldr pc,=#0x30000014 //Abort data
	ldr pc,=#0x30000018 //Reserved
	ldr pc,=#0x3000001C //IRQ
	ldr pc,=#0x30000020 //FIQ
.end
	
