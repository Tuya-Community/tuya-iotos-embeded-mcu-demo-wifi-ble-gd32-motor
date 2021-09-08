#include "gd32e23x.h"
#include "systick.h"
#include <stdio.h>

#include <led.h>
#include <delay.h>
#include <usart.h>
#include <wifi.h>
#include <key.h>
#include <pwm.h>

uint32_t USART0_RECEIVE_Buf[100]; 
uint32_t USART1_RECEIVE_Buf[100]; 
extern void Connect_Wifi(void);
extern uint32_t pulse;
extern unsigned char fwd_flag;
extern unsigned char rev_flag;
extern unsigned char vlo_flag;
extern unsigned char stop_flag;

int main(void)
{
    systick_config();   
		LED_Init();  
	  wifi_protocol_init();//wifi协议初始化
		USART0_Init();
		USART1_Init();
	  Key_Init();
    PWM_Config();
	
 while(1)
		{
	  	wifi_uart_service();//wifi串口数据处理服务
			Key_Deal();
  if(stop_flag==0)
	{ 
		if(fwd_flag==1)
	  {
			timer_channel_output_pulse_value_config(TIMER2,TIMER_CH_0,0);
		  timer_channel_output_pulse_value_config(TIMER2,TIMER_CH_1,pulse);
			Delay_ms(10);
			timer_channel_output_pulse_value_config(TIMER2,TIMER_CH_0,pulse);	
			timer_channel_output_pulse_value_config(TIMER2,TIMER_CH_1,0);
		}
	else  if(rev_flag==1)
	 {
		 
		 timer_channel_output_pulse_value_config(TIMER2,TIMER_CH_0,pulse);	
		 timer_channel_output_pulse_value_config(TIMER2,TIMER_CH_1,0);
		 Delay_ms(10);
		 timer_channel_output_pulse_value_config(TIMER2,TIMER_CH_0,0);
		 timer_channel_output_pulse_value_config(TIMER2,TIMER_CH_1,pulse);	
	 }
	else  if(vlo_flag==1)
	 {
	   timer_channel_output_pulse_value_config(TIMER2,TIMER_CH_1,0);
		 timer_channel_output_pulse_value_config(TIMER2,TIMER_CH_0,0);
	 }
  }
	else if(stop_flag==1)
	 {
	   timer_channel_output_pulse_value_config(TIMER2,TIMER_CH_1,1000);
		 timer_channel_output_pulse_value_config(TIMER2,TIMER_CH_0,1000);
	 } 
   	//printf("X:%d\r\n",pulse);
	  mcu_dp_value_update(DPID_PWM,pulse/10); //调整PWM输出占空比，然后上传到平台
	 }
}