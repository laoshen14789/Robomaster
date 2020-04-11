#include "shangdao.h"
#include "USER_chassis.h"

int aaa=0,bbb=0,ccc=0,ddd=0,eee=0;
int qian=0,hou=0;
int flag=0;
int youben=0;
 float MAX_WHEEL_SPEED11 = 500;
 double rcch11[4];
 double rcch22[4];
 double zhuazi[1];
 int16_t Speed11[3];
 int16_t Speed22[4];
void shangdaoPIDInit(void){

	
	my_can_filter_init_recv_all(&hcan1);
	HAL_CAN_Receive_IT(&hcan1, CAN_FIFO0);
	HAL_CAN_Receive_IT(&hcan2, CAN_FIFO0);
	
	
	

	
	for(int i=0; i<3; i++)
	{
		PID_struct_init(&pid_spd1[i], POSITION_PID, 20000, 20000,
									SHANGDAO_KP,	SHANGDAO_KI,	SHANGDAO_KD	);  //3 motos angular rate closeloop.
	}
	


}

void shangdao_moto_on(void){
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_3, GPIO_PIN_SET);

}

void shangdao_moto_off(void){
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_3, GPIO_PIN_RESET);
	
}

	

void Set_shangdao_Current(int16_t set_spd[]){
	
	#ifdef NORMAL

		for(int i=0; i<3; i++)
		{
			pid_calc(&pid_spd1[i], moto_shangdao[i].speed_rpm, set_spd[i]);
		}
		if(Key.Posision.Q|Key.Posision.E|Key.Posision.R)
		set_moto_current(&hcan1, 0, 
								0,
								pid_spd1[2].pos_out,
								0, 
								0x01);

		else		set_moto_current(&hcan1, pid_spd1[0].pos_out, 
								pid_spd1[1].pos_out,
								0,
								0, 
								0x01);

		osDelay(5);
		#endif
		
	#ifdef DEBUG
	for(int i=0; i<3; i++)
			{
			pid_calc(&pid_spd1[i], moto_shangdao[i].speed_rpm, set_spd[i]);
		}
					set_moto_current(&hcan1, 0, 
								0,
								pid_spd1[2].pos_out,
								0, 
								0x01);
		osDelay(5);
	#endif
}

int hongwai(){
	#ifdef DEBUG
	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4)==GPIO_PIN_RESET) bbb=1;
		else bbb=0;
	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_5)==GPIO_PIN_RESET) ccc=1;
		else ccc=0;
	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_6)==GPIO_PIN_RESET) ddd=1;
		else ddd=0;
	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_12)==GPIO_PIN_RESET) eee=1;
		else eee=0;
	
	#endif
	
	#ifdef NORMAL
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_6)==GPIO_PIN_RESET &
	HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_12)==GPIO_PIN_RESET &
	HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4)==GPIO_PIN_RESET & 
	HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_5)==GPIO_PIN_RESET){

		return ALL;

}
	
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_6)==GPIO_PIN_SET &
	HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_12)==GPIO_PIN_SET &
	HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4)==GPIO_PIN_SET & 
	HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_5)==GPIO_PIN_SET){
		
		return NONE;	
	}
	

	
	if (HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4)==GPIO_PIN_RESET &
		HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_5)==GPIO_PIN_RESET &&
	HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_6)==GPIO_PIN_SET &
	HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_12)==GPIO_PIN_SET){

		
		return BACK;		
	}
	
	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_6)==GPIO_PIN_RESET &
	   HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_12)==GPIO_PIN_RESET &&
		HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4)==GPIO_PIN_SET &
		HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_5)==GPIO_PIN_SET){
		
		return FRONT;	
	}
	#endif
		return 4;
	}


void shangshen(){ //上岛
	//hongwai();
	if(hongwai()==ALL ){
			shangdao_moto_on();
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, GPIO_PIN_SET);//
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_RESET);//上升
		
		osDelay(5000);
		shangdao_moto_off();
		flag=1;
		
		
	}
	if(hongwai()==NONE)
		lunzi();
	if(hongwai()==FRONT & hongwai()!=BACK ){	
		

			shangdao_moto_on();
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, GPIO_PIN_RESET);//
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_SET);//下降
			osDelay(5000);
			shangdao_moto_off();
		flag=0;
	}
	
}

void xiajiang(){//下岛
		if(  hongwai()==FRONT && hongwai()!=BACK ){
			shangdao_moto_on();
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, GPIO_PIN_SET);//
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_RESET);//上升
			osDelay(5000);
			shangdao_moto_off();

		}
		   if(hongwai()==NONE){

			  shangdao_moto_on();
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, GPIO_PIN_RESET);//
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_SET);//下降
			  osDelay(5000);
			shangdao_moto_off();
		}
}

void lunzi(){
			rcch22[0] = -rc.ch1*10;
			rcch22[1] = rc.ch2*10;
			rcch22[2] = -rc.ch3*10;
			Mecanum_calc(rcch22[0], rcch22[1], rcch22[2], MAX_WHEEL_SPEED11, Speed22);
			Set_M620_Current(Speed22);
			//osDelay(5);
			rcch11[1] = rc.ch2*10;
			Speed11[0]=-rcch11[1];
			Speed11[1]=rcch11[1];
			Set_shangdao_Current(Speed11);

}





void tinzhi(){
			memset(Speed22,0,sizeof(Speed22));
			memset(Speed11,0,sizeof(Speed11));
			Set_M620_Current(Speed22);
			Set_shangdao_Current(Speed11);
			shangdao_moto_on();
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_SET);//推杆下降复位

}

void zhuazi1(){

	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_RESET &&//前
	   HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)==GPIO_PIN_SET){

			zhuazi[0]=200;
			Speed11[0]=zhuazi[0];


		
		}
	   

}


void zhuaquqian(){//爪子向前
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_SET &//碰到后面传感器
			HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)==GPIO_PIN_RESET ||
			HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_SET &//在前后传感器之间
			HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)==GPIO_PIN_SET){	
				__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1,1500);//油泵开
				__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2,1000);//爪子张开
			zhuazi[0]=-500;
			Speed11[2]=zhuazi[0];
			
			Set_shangdao_Current(Speed11);
				//Set_zhuazi_Current(Speed11);
				
		}
			
		else{
			if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_RESET &//碰到前面传感器
			HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)==GPIO_PIN_SET)
			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1,1500);//油泵开
			youben=1;
				__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2,2000);//爪子合上
			memset(Speed22,0,sizeof(Speed22));
			memset(Speed11,0,sizeof(Speed11));
			Set_M620_Current(Speed22);
			Set_shangdao_Current(Speed11);
			//Set_zhuazi_Current(Speed11);

			}

}

void zhuaquhou(){//爪子向后
	#ifdef DEBUG
	
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_RESET &//碰到前面传感器
			HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)==GPIO_PIN_SET) qian=1;
	else qian=0;
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_SET &//碰到后面传感器
			HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)==GPIO_PIN_RESET) hou=1;
	else hou=0;
	#endif
	
	#ifdef NORMAL
			if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_RESET &//碰到前面传感器
			HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)==GPIO_PIN_SET ||
			HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_SET &//在前后传感器之间
			HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)==GPIO_PIN_SET){
				
				
			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1,1500);//油泵开
			if(youben==1){__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, 2000);//爪子合上
				youben=0;
			}				
			zhuazi[0]=300;
			Speed11[2]=zhuazi[0];
			Set_shangdao_Current(Speed11);
				
			//Set_zhuazi_Current(Speed11);
				
				
		}
			
			else{
			
			//	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1,1000);//油泵关
			memset(Speed22,0,sizeof(Speed22));
			memset(Speed11,0,sizeof(Speed11));
				//osDelay(5);
			Set_M620_Current(Speed22);
			Set_shangdao_Current(Speed11);
			//Set_zhuazi_Current(Speed11);
			
			}
	
	#endif
}

void zhuaqutin(){//抓子停
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_SET &//碰到后面传感器
			HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)==GPIO_PIN_RESET ||
			HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_SET &//在前后传感器之间
			HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)==GPIO_PIN_SET){
				//__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1,1500);//油泵开
			zhuazi[0]=-700;
			Speed11[2]=zhuazi[0];
			Set_shangdao_Current(Speed11);
				//Set_zhuazi_Current(Speed11);
			
			}
			else{
				__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1,1500);//油泵开
				youben=3;
			memset(Speed22,0,sizeof(Speed22));
			memset(Speed11,0,sizeof(Speed11));
			Set_M620_Current(Speed22);
			Set_shangdao_Current(Speed11);
			//Set_zhuazi_Current(Speed11);
			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, 1000);//爪子张开	
			}
			
}

	
void shangdao_Task(void const * argument){
	
	ShangdaoTask_Init();
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, 1000);
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, 1500);
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, 2400);
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 700);
	//__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_3, 1500);
	//__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_2, 1500);
	for(;;){
		
		ShangdaoTask_Loop();
		osThreadYield();
		
		
	}

}


