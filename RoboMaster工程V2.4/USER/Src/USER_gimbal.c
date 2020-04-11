#include "USER_gimbal.h"

int16_t mouse_move_angle = 0;
uint8_t mouse_click_shoot = 0;

void GimTask_Init(void){
	
	extern rc_info_t rc;
	GimbalInit();

}

void GimTask_Loop(void){
	
	Angle_transimit();
		
	switch (keystate){
		
		case KEY_OFF_UP:
			TIM2->CCR1 = 1000;
			TIM2->CCR2 = 1000;
		case KEY_CL_UP:
		case KEY_HL_UP:
			//Set_Gimbal_Current(0, 0, 0);
			//TIM12->CCR1 = 1000;
			break;
		
		case KEY_OFF_MD:
			TIM2->CCR1 = 0;
			TIM2->CCR2 = 0;
		case KEY_CL_MD:
		case KEY_HL_MD:
			//Set_Gimbal_Current(rc.sw, -rc.ch4, 0);
			//TIM12->CCR1 = 1000;
			break;
		
		case KEY_OFF_DN:
			TIM2->CCR1 = -1000;
			TIM2->CCR2 = -1000;
		case KEY_CL_DN:
			//TIM12->CCR1 = 2000;
			//Set_Gimbal_Current(rc.sw, -rc.ch4, 1200);
			break;
		
		case KEY_HL_DN:
			//MouseContral();
			break;
		
		default:
			break;
	}
	
}

void MouseContral(void){
	
	mouse_move_angle = mouse_move_angle + rc.mouse.y;
	(mouse_move_angle> 660)?(mouse_move_angle= 660):(mouse_move_angle);
	(mouse_move_angle<-660)?(mouse_move_angle=-660):(mouse_move_angle);
	
	(rc.mouse.press_r)?(TIM12->CCR1 = 1300):(TIM12->CCR1 = 1000);
	(rc.mouse.press_r && rc.mouse.press_l)?(mouse_click_shoot = 10):(mouse_click_shoot = 0);
	
	Set_Gimbal_Current(rc.sw, mouse_move_angle, mouse_click_shoot*100);
	
}
