#ifndef GPIO_BUTTON_H_

#define GPIO_BUTTON_H_

#include "common.h"
#include "gpio_def.h"

void init_gpio_button();

/*
 * Note: Comparison with 0 because the pins are pulled up.
 * If button is pressed it is logic 0 i.e. the pin sinks the current.
 * If button is pressed it is logic 1 or Vcc
 */
#define is_btn_K1_pressed(BA) 	\
	((readreg32(GPDAT_REG(BA)) & K1_GPIO_BTN) == 0)

#define is_btn_K2_pressed(BA) 	\
	((readreg32(GPDAT_REG(BA)) & K2_GPIO_BTN) == 0)

#define is_btn_K3_pressed(BA) 	\
	((readreg32(GPDAT_REG(BA)) & K3_GPIO_BTN) == 0)

#define is_btn_K4_pressed(BA) 	\
	((readreg32(GPDAT_REG(BA)) & K4_GPIO_BTN) == 0)

#define is_btn_K5_pressed(BA) 	\
	((readreg32(GPDAT_REG(BA)) & K5_GPIO_BTN) == 0)

#define is_btn_K6_pressed(BA) 	\
	((readreg32(GPDAT_REG(BA)) & K6_GPIO_BTN) == 0)


#endif
