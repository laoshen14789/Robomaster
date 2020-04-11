/**
 ***************************************(C) COPYRIGHT 2019 TJUT***************************************
 * @file       keyscan.c
 * @brief      
 * @note         
 * @Version    V1.0.0
 * @Date       Mar-09-2019      
 ***************************************(C) COPYRIGHT 2019 TJUT***************************************
 */
 
#include "keyscan.h"

uint8_t keystate;

void key_scan(void){
	
	if(rc.sw1 == 1){
		
		switch (rc.sw2){
			
			case 1:
				keystate = KEY_OFF_UP;
			break;
			
			case 3:
				keystate = KEY_OFF_MD;
			break;
			
			case 2:
				keystate = KEY_OFF_DN;
			break;
		}
	}
	
	if(rc.sw1 == 3){
		
		switch (rc.sw2){
			
			case 1:
				keystate = KEY_CL_UP;
			break;
			
			case 3:
				keystate = KEY_CL_MD;
			break;
			
			case 2:
				keystate = KEY_CL_DN;
			break;
		}
	}
	
	if(rc.sw1 == 2){
		
		switch (rc.sw2){
			
			case 1:
				keystate = KEY_HL_UP;
			break;
			
			case 3:
				keystate = KEY_HL_MD;
			break;
			
			case 2:
				keystate = KEY_HL_DN;
			break;
		}
	}
}

void keycheck(void){
	
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	TIM3->CCR1 = 1000;
	
	for(;;){
		key_scan();
		TIM3->CCR1 = 2000;
		if(keystate == KEY_OFF_UP){
			break;
		}
		TIM3->CCR1 = 1000;
	}
	
}
