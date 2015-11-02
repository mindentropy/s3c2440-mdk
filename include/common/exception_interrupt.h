#ifndef EXCEPTION_INTERRUPT_H_

#define EXCEPTION_INTERRUPT_H_


#define EXCEPTION_INTERRUPT_VECTOR_TABLE_START 0x33F00000


void blink_led_test() __attribute__((section(".isrhandler")));

void do_handle_undef() __attribute__((section(".isrhandler")));
void do_handle_swi() __attribute__((section(".isrhandler")));
void do_handle_dabt() __attribute__((section(".isrhandler")));
void do_handle_pabt() __attribute__((section(".isrhandler")));
void do_handle_irq() __attribute__((section(".isrhandler")));
void do_handle_fiq() __attribute__((section(".isrhandler")));

#endif
