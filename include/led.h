#ifndef LED_H_

#define LED_H_

#include "common.h"


#define LED1 	BIT(5)
#define LED2    BIT(6)
#define LED3    BIT(7)
#define LED4    BIT(8)

void init_led();
void led_on(unsigned led);
void led_off(unsigned led);

#endif
