#ifndef  PWM_H
#define  PWM_H

#include "gd32e23x.h"

#define PWM_OUT_PORT_CLK  RCU_GPIOA
#define PWM_OUT_PORT  GPIOA
#define PWM_OUT_PIN1  GPIO_PIN_6
#define PWM_OUT_PIN2  GPIO_PIN_7

void PWM_Config(void);
	
#endif

