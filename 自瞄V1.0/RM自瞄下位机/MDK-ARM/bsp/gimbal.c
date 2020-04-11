#include "gimbal.h"
//#include "bsp_uart.h"
int xxx,yyy;
uint8_t zzz[8]="12345";
void GimbalPIDInit(void){

		PID_struct_init(&pid_yaw, POSITION_PID, 2000, 2000,
									20,	1,	15	);  //angular rate closeloop.

		PID_struct_init(&pid_pit, POSITION_PID, 2000, 2000,
									3,	1,	5	);  //4 motos angular rate closeloop.

}

void Set_Gimbal_Current(int16_t yaw_target_spd, int16_t pit_target_spd, int16_t set_spd){
	
	pid_calc(&pid_yaw, moto_yaw.real_angle + moto_yaw.offset_angle, yaw_target_spd);
	pid_calc(&pid_pit, moto_pit.real_angle + moto_pit.offset_angle, pit_target_spd);
	//pid_calc(&pid_poke, moto_poke.speed_rpm, set_spd);

	set_moto_current(&hcan1, 
									 pid_yaw.pos_out,
									 pid_pit.pos_out, 
									 0, 
									 0,
									 0x01);




	osDelay(10);

}

void Angle_transimit(void){
	
	moto_pit.real_angle = (moto_pit.correcting_angle >= 4096)?
		(((moto_pit.angle <= 8192 && moto_pit.angle > moto_pit.correcting_angle-4096)?(moto_pit.angle):(moto_pit.angle+8192)) - moto_pit.correcting_angle):
		(((moto_pit.angle <= 8192 && moto_pit.angle > moto_pit.correcting_angle+4096)?(moto_pit.angle-8192):(moto_pit.angle)) - moto_pit.correcting_angle);
	
	
	
	
	moto_yaw.real_angle = (moto_yaw.correcting_angle >= 4096 )?
		(((moto_yaw.angle <= 8192 && moto_yaw.angle > moto_yaw.correcting_angle-4096)?(moto_yaw.angle):(moto_yaw.angle+8192)) - moto_yaw.correcting_angle):
		(((moto_yaw.angle <= 8192 && moto_yaw.angle > moto_yaw.correcting_angle+4096)?(moto_yaw.angle-8192):(moto_yaw.angle)) - moto_yaw.correcting_angle);
	
}

void Gimbal_Task(void const * argument){
	moto_pit.correcting_angle=0;
	moto_yaw.correcting_angle=2000;
	uartinit();
	GimbalPIDInit();
	
	for(;;){ 
			//trans(&xxx,&yyy);
		
		//HAL_UART_Transmit(&huart6,rx,sizeof(rx),10);//·¢ËÍ´®¿Ú
		//printf("%d\n",xxx);
			Angle_transimit();
			Set_Gimbal_Current(0,0,0);
		osThreadYield();
		
	}
	
	
}
