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
extern union KEY_Reg key;
KEY_STATE click;

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
	
	click_check();
}

void IOInit(void){
	
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
	
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_5, GPIO_PIN_SET);
	
	for(;;){
		key_scan();
		if(keystate == KEY_OFF_UP){
			break;
		}
		TIM12->CCR1 = 250;
	}
			
	TIM12->CCR1 = 0;
}

void click_check(void){
	
	if(key.Posision.X)
	{
		while(key.Posision.X)osDelay(1);
		click.X = 1 - click.X;
	}
	
}
