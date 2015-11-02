#ifndef EXCEPTION_INTERRUPT_H_

#define EXCEPTION_INTERRUPT_H_


#define EXCEPTION_INTERRUPT_VECTOR_TABLE_START 0x33F00000


void blink_led_test() __attribute__((section(".isrhandler")));


#endif
