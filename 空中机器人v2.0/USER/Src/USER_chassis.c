#include "USER_chassis.h"

float MAX_WHEEL_SPEED = 6000;
double rcch[4];
int16_t Speed[4];
union KEY_Reg key;

void ChsTask_Init(void){
	
	extern rc_info_t rc;

	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);
		
	my_can_filter_init_recv_all(&hcan1);
	HAL_CAN_Receive_IT(&hcan1, CAN_FIFO0);
	HAL_CAN_Receive_IT(&hcan2, CAN_FIFO0);
	
}

void ChsTask_Loop(void){
		key.value = rc.key;
	
	switch (keystate){
								
		case KEY_OFF_UP:
		case KEY_OFF_MD:
		case KEY_OFF_DN:
     
		
			break;
		
		case KEY_CL_UP:
		case KEY_CL_MD:
		case KEY_CL_DN:
//		//  rcch[0] = -rc.ch1*10;
//			rcch[1] = ((rc.ch2*500)/660)+1500;
//			//rcch[2] = -rc.ch3*10;
//			TIM5->CCR3 =rcch[1];
//			TIM5->CCR2 = 3000-rcch[1];
			break;
		
//		case KEY_HL_UP:
		case KEY_HL_DN:
//				 rcch[1] = ((rc.ch2*500)/660)+1500;
//			//rcch[2] = -rc.ch3*10;
//			TIM5->CCR3 =rcch[1];
//			TIM5->CCR2 = 3000-rcch[1];

//			
		
		
//			Mecanum_calc(rcch[0], rcch[1], rcch[2], MAX_WHEEL_SPEED, Speed);
//			Set_M620_Current(Speed);
			break;
		
//		case KEY_HL_DN:
//			KeyboardContral();
//			break;
		
		default:
			break;
			
		}
	
}

void KeyboardContral(void){

	rcch[1] = key.Posision.W*(-3000) + key.Posision.S*(3000);
	rcch[0] = key.Posision.D*(-3000) + key.Posision.A*(3000);
	
	if(key.Posision.SHIFT || key.Posision.CTRL){
		
		if(key.Posision.SHIFT){
			rcch[1] *= 2;
			rcch[0] *= 2;
		}
		else if(key.Posision.CTRL){
			rcch[1] *= 0.5;
			rcch[0] *= 0.5;
		}
	
	}

	rcch[2] = -rc.mouse.x*100;
		
	Mecanum_calc(rcch[0], rcch[1], rcch[2], MAX_WHEEL_SPEED, Speed);
	Set_M620_Current(Speed);
}
