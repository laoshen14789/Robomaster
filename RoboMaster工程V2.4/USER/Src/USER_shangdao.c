#include "USER_shangdao.h"
#include "USER_chassis.h"
//#include "remotecontrol.h"
double rcch1[2];
double rcch2[4];
int16_t Speed1[2];
int16_t Speed2[4];
int mouse1=0;
int camera=0;
int ben=0;
int fff=0;

//union KEY_Reg key1;
extern union KEY_Reg Key;
float MAX_WHEEL_SPEED1 = 500;


void ShangdaoTask_Init(void){

	extern rc_info_t rc;
	shangdaoPIDInit();
	
}


void ShangdaoTask_Loop(void){
	
	switch (keystate){
							
		case KEY_OFF_UP://左边开关上，右边开关上
			shangdao_moto_off();

			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, 1000);
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, 2400);
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 700);//关盖

			break;
		case KEY_OFF_MD://左边开关上，右边开关中
			shangdao_moto_off();
			//__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, 1000);
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, 2400);
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 700);//关盖
		Keyboard();

			break;
		case KEY_OFF_DN://左边开关上，右边开关下
			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, 1000);
			shangdao_moto_on();
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_SET);//推杆下降复位

	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, 1180);
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 1880);//开盖
			break;
		
		case KEY_CL_UP:
		shangdao_moto_off();
			#ifdef NORMAL
			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, 1500);//开油泵
			zhuaquqian();
			#endif
		break;
		
		case KEY_CL_MD:
//zhuazi1();	
		shangdao_moto_off();
		#ifdef NORMAL
		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, 1500);//开油泵
		zhuaquhou();
		#endif
		
		#ifdef DEBUG
		zhuaquhou();
		rcch2[0] = -rc.ch1*10;
		Speed2[2]=rcch2[0];
		Set_shangdao_Current(Speed2);
			shangdao_moto_off();
		#endif
			break;
		
		case KEY_CL_DN:
		shangdao_moto_off();
			#ifdef NORMAL
		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, 1500);//开油泵
			zhuaqutin();
			#endif
			break;

		
		case KEY_HL_DN://下岛
			#ifdef NORMAL
			lunzi();//下岛小轮启动
			if(hongwai()==NONE)	
			tinzhi();//所有轮子停止转动
		    xiajiang();//下岛程序	
			#endif
			
			break;

		case KEY_HL_MD:
			shangdao_moto_off();
		#ifdef NORMAL
		if(hongwai()==NONE){tinzhi();}
		else{
			rcch2[0] = -rc.ch1*10;
			rcch2[1] = rc.ch2*10;
			rcch2[2] = -rc.ch3*10;
			Mecanum_calc(rcch2[0], rcch2[1], rcch2[2], MAX_WHEEL_SPEED1, Speed2);
			Set_M620_Current(Speed2);
			//osDelay(5);
			rcch1[1] = rc.ch2*10;
			Speed1[0]=-rcch1[1];
			Speed1[1]=rcch1[1];
			Set_shangdao_Current(Speed1);
		}
		#endif
		
		#ifdef DEBUG
		hongwai();
		#endif
		break;
			
		case KEY_HL_UP://上岛
			
			#ifdef NORMAL
		
			shangshen();
			#endif
			break;

		
		default:
			break;
			
		}
	
}
void keyboard_xiadao(){
			lunzi();//下岛小轮启动
			if(hongwai()==NONE)	
			tinzhi();//所有轮子停止转动
		    xiajiang();//下岛程序
}



void Keyboard(){

				if(	HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_SET &//在前后传感器之间
			HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)==GPIO_PIN_SET || 
				HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_RESET &//碰到前面传感器
			HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)==GPIO_PIN_SET)
			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1,1500);//油泵开

	else	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1,1000);//油泵关
				if(Key.Posision.V==1){ 
					osDelay(70);
					if(Key.Posision.V==1)
					mouse1=~mouse1;
				}

			
				if(Key.Posision.B){
				__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, 1200);
				__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 2000);//开盖
			}
	else {
				__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, 2000);
				__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 700);//关盖
	
			}
	if(Key.Posision.Z) shangshen();
	if(Key.Posision.C) keyboard_xiadao();
	if(Key.Posision.X) tinzhi();
	if(mouse1) HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_RESET);
		else  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_SET);
	if(Key.Posision.F) {
		osDelay(70);
				if(Key.Posision.F) camera=~camera;
	}
	

	if(Key.Posision.Q){
			__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_2, 1100);
			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, 1500);//开油泵	
			zhuaquqian();
		}			
	if(Key.Posision.E){
			__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_2, 1100);
			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, 1500);//开油泵
			zhuaquhou();
	}
	if(Key.Posision.R){
			__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_2, 1100);
			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, 1500);//开油泵
			zhuaqutin();
	}
		if(camera ){
		__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_3, 1000);
		__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_2, 1600);
	}
		
	
	else {
		//__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, 1000);//关油泵
		__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_3, 2000);
		__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_2, 1500);
	}



}
	
