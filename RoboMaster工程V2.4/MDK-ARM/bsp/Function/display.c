#include "display.h"
#include "remotecontrol.h"
#include "chassis.h"
#include "bsp_imu.h"

extern void Tell_the_FUCKING_Graphic_Card_TO_Display(void){
	char hello_world[]="Tell the FUCKING Graphic Card TO Display Hello World";
	/* Display mode Initial */
	oled_clear(Pen_Clear);
	oled_LOGO();
	oled_refresh_gram();
	HAL_Delay(1000);
	oled_clear(Pen_Clear);
	//oled_shownum(0, 0, 1234567890,0x01,10); 
	oled_refresh_gram();
	for(int i=0;i<17;i++){
			oled_showchar(0,1+i,hello_world[i]);
		}
	for(int i=0;i<16;i++){
			oled_showchar(1,1+i,hello_world[17+i]);
		}
	for(int i=0;i<19;i++){
			oled_showchar(2,1+i,hello_world[33+i]);
		}
	oled_refresh_gram();
	HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);   
	
	HAL_Delay(1000);
	oled_clear(Pen_Clear);
	oled_refresh_gram();
}

void Display_Task(void const * argument){
	extern rc_info_t rc;
	extern imu_t  imu;
	int haveData;

	
	char txt[]="CH1:CH2:CH3:CH4:";
	
	oled_clear(Pen_Clear);
	oled_refresh_gram();
		
	for(;;){		
		

		switch (rc.sw1){
			
			case 1:		
				oled_LOCK();
				haveData = 1;
				break;
			
			case 3:
				if(haveData != 0){
					oled_clear(Pen_Clear);
					oled_refresh_gram();
					haveData = 0;
				}
				
				for(int i=0;i<4;i++){
						oled_showchar(0,1+i,txt[i]);
					}
				for(int i=4;i<8;i++){
						oled_showchar(1,1+i-4,txt[i]);
					}
				for(int i=8;i<12;i++){
						oled_showchar(2,1+i-8,txt[i]);
					}
				for(int i=12;i<16;i++){
						oled_showchar(3,1+i-12,txt[i]);
					}
				oled_refresh_gram();
					
				(rc.ch1>=0) ? (oled_showchar(0,6,' ')) : (oled_showchar(0,6,'-'));
				(rc.ch2>=0) ? (oled_showchar(1,6,' ')) : (oled_showchar(1,6,'-'));
				(rc.ch3>=0) ? (oled_showchar(2,6,' ')) : (oled_showchar(2,6,'-'));
				(rc.ch4>=0) ? (oled_showchar(3,6,' ')) : (oled_showchar(3,6,'-'));
					
				
				oled_shownum(0, 7, MyAbs(rc.ch1), 0x00, 3);
				oled_shownum(1, 7, MyAbs(rc.ch2), 0x00, 3);
				oled_shownum(2, 7, MyAbs(rc.ch3), 0x00, 3);
				oled_shownum(3, 7, MyAbs(rc.ch4), 0x00, 3);
				break;
					
			default:
				break;
		}
		
		osThreadYield();
		
	} 

}

void display_imu(void const * argument){
	extern imu_t  imu;
	char buf[300];
	
	while(1){
		mpu_get_data();
		imu_ahrs_update();
		imu_attitude_update(); 
		HAL_Delay(5);		
		oled_shownum(0, 1, 22, 0x00, 8);
		oled_shownum(0, 1, imu.rol, 0x00, 8);
		oled_shownum(1, 1, imu.pit, 0x00, 8);
		oled_shownum(2, 1, imu.yaw, 0x00, 8);
		oled_shownum(3, 1, imu.temp, 0x00, 8);
		sprintf(buf, " Roll: %8.3lf    Pitch: %8.3lf    Yaw: %8.3lf\n", imu.rol, imu.pit, imu.yaw);
		HAL_Delay(5);		
			
	}
	
}
