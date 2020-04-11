#include "stm32f4xx_hal.h"
#include "cmsis_os.h" 
#include "bsp_can.h"
#include "bsp_uart.h"
#include "can.h"
#include "pid.h"
#include "tim.h"
#include <math.h>
#include "mytype.h"

void GimbalPIDInit(void);
//void GimbalInit(void);
void Set_Gimbal_Current(int16_t yaw_target_spd, int16_t pit_target_spd, int16_t set_spd);
//void Set_GM6020_Current(int16_t target_spd);
void Angle_transimit(void);
void Gimbal_Task(void const * argument);


