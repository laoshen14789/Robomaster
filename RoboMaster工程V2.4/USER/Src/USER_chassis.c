#include "USER_chassis.h"
#include "USER_shangdao.h"

float MAX_WHEEL_SPEED = 6000;
double rcch[4];
int16_t Speed[4];
int16_t Speed_shangdao[2];
union KEY_Reg Key;

void ChsTask_Init(void){
	
	extern rc_info_t rc;
	ChassisPIDInit();
	
}

void ChsTask_Loop(void){
		Key.value = rc.key;
	
	switch (keystate){
								
		case KEY_OFF_UP:
			shangdao_moto_off();
			rcch[0] = -rc.ch1*10;
			rcch[1] = rc.ch2*10;
			rcch[2] = -rc.ch3*10;
			Mecanum_calc(rcch[0], rcch[1], rcch[2], MAX_WHEEL_SPEED, Speed);
			Set_M620_Current(Speed);
			break;
		
		case KEY_OFF_MD:
//			shangdao_moto_off();
//			memset(Speed,0,sizeof(Speed));
//			memset(rcch,0,sizeof(rcch));
//			Set_M620_Current(Speed);
			KeyboardContral();
		
		
			break;
			
		case KEY_OFF_DN:
			//KeyboardContral();
			break;
		
		case KEY_CL_UP:
		case KEY_CL_MD:
		case KEY_CL_DN:
			shangdao_moto_off();
			memset(Speed,0,sizeof(Speed));
			memset(rcch,0,sizeof(rcch));
			Set_M620_Current(Speed);
			break;
		
		case KEY_HL_UP:
		case KEY_HL_MD:
		case KEY_HL_DN:
			//KeyboardContral();
			break;
		
		default:
			break;
			
		}
	
}

void KeyboardContral(void){
	
	rcch[1] = Key.Posision.W*(4000) + Key.Posision.S*(-4000);
	rcch[0] = Key.Posision.D*(-4000) + Key.Posision.A*(4000);
	
	
	if(Key.Posision.SHIFT || Key.Posision.CTRL){
		
		if(Key.Posision.SHIFT){
			rcch[1] *= 2;
			rcch[0] *= 2;
		}
		else if(Key.Posision.CTRL){
			rcch[1] *= 0.5;
			rcch[0] *= 0.5;
		}
	
	}

	rcch[2] = -rc.mouse.x*100;
	Speed_shangdao[0]=-rcch[1];
	Speed_shangdao[1]=rcch[1];
	Set_shangdao_Current(Speed_shangdao);
	Mecanum_calc(rcch[0], rcch[1], rcch[2], MAX_WHEEL_SPEED, Speed);
	//Set_shangdao_Current(Speed_shangdao);
	if(Key.Posision.W|Key.Posision.S|Key.Posision.A|Key.Posision.D|rc.mouse.x)
	Set_M620_Current(Speed);
	
	else 		set_moto_current(&hcan1, 0, 
								0,
								0,
								0, 
								0x00);

}
