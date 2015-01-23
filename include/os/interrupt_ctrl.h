#ifndef INTERRUPT_CTRL_H_
#define INTERRUPT_CTRL_H_

struct interrupt_regs {
	unsigned int SRCPND; /* Source pending register */
	unsigned int INTMOD; /* Interrupt mode register */
	unsigned int INTMSK; /* Interrupt mask register */
	unsigned int INTPND; /* Interrupt pending register */
	unsigned int INTOFFSET; /* Interrupt offset register */
	unsigned int SUBSRCPND; /* Sub source pending register */
	unsigned int INTSUBMSK; /* Interrupt sub mask register */
};

#endif
