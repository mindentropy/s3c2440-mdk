#ifndef EXCEPTION_INTERRUPT_H_

#define EXCEPTION_INTERRUPT_H_

#include "interrupt.h"


void handle_irq(void);
void test_blink_led(void);

void add_irq_handler(enum int_offset INT_OFFSET,
						void (*interrupt_handler)(void));

void init_jmp_table(void);

#endif
