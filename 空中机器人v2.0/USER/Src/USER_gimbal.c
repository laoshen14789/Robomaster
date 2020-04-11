#include "USER_gimbal.h"
double rcch1[4];
int16_t mouse_move_angle = 0;
uint8_t mouse_click_shoot = 0;
extern KEY_STATE click;
int16_t   YAWOUT;
int16_t   POKEOUT;
void GimTask_Init(void){
	
	extern rc_info_t rc;
	GimbalInit();

}

void GimTask_Loop(void){
	
	Angle_transimit();
		
	switch (keystate){
		
		case KEY_OFF_UP:
		case KEY_CL_UP:
		case KEY_HL_UP:
			Set_Gimbal_Current(0, 0, 0);
			TIM2->CCR1 = 1000;
			TIM2->CCR2 = 1000;
			TIM5->CCR3 = 1500;
			TIM5->CCR2 = 1500;
			LASER_OFF;
			break;
		
		case KEY_OFF_MD:
		case KEY_CL_MD:
		case KEY_HL_MD:
			Set_Gimbal_Current(rc.ch1, 0, 0);
			TIM2->CCR1 = 1000;
			TIM2->CCR2 = 1000;
			rcch1[1] = ((-rc.ch2*500)/660)+1500;
			TIM5->CCR3 =rcch1[1];
			TIM5->CCR2 = 3000-rcch1[1];
			LASER_OFF;
			break;
		
		case KEY_OFF_DN:
		case KEY_CL_DN:
		case KEY_HL_DN:

			TIM2->CCR1 = 1500;
			TIM2->CCR2 = 1500;
		 YAWOUT=rc.ch1+rc.ch3*3;
		POKEOUT=POKEOUT+rc.sw;
		POKEOUT=-abs(POKEOUT)/2;
		Set_Gimbal_Current(YAWOUT, 0, POKEOUT);
			rcch1[1] = ((-rc.ch2*500)/660)+1500;
			TIM5->CCR3 =rcch1[1];
			TIM5->CCR2 = 3000-rcch1[1];
			LASER_ON;
			break;
		
		

		
		default:
			break;
	}
	
}

void MouseContral(void){
	
	mouse_move_angle = mouse_move_angle + rc.mouse.y;
	(mouse_move_angle> 660)?(mouse_move_angle= 660):(mouse_move_angle);
	(mouse_move_angle<-660)?(mouse_move_angle=-660):(mouse_move_angle);
	
	(rc.mouse.press_r)?(TIM2->CCR1 = 1300):(TIM2->CCR1 = 1000);
	(rc.mouse.press_r && rc.mouse.press_l)?(mouse_click_shoot = 10):(mouse_click_shoot = 0);
	
	Set_Gimbal_Current(rc.sw, mouse_move_angle, mouse_click_shoot*100);
	
	if(click.X){LASER_ON}else LASER_OFF;
		
}
