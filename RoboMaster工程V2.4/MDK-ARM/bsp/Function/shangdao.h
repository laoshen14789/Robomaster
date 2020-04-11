#ifndef __SHANGDAO_H__
#define __SHANGDAO_H__

#include "stm32f4xx_hal.h"
#include "cmsis_os.h" 
#include "bsp_can.h"
#include "can.h"
#include "pid.h"
#include "tim.h"
#include "keyscan.h"
#include "remotecontrol.h"
#include "USER_DEFINITION.h"
#include "USER_shangdao.h"
#include <math.h>
#define NORMAL
#define FRONT 1 
#define BACK 5 
#define NONE  2 
#define ALL  3 





void shangdao_Task(void const * argument);
void Set_shangdao_Current(int16_t set_spd[]);
void shangdaoPIDInit(void);
void shangdao_moto_off(void);
void shangdao_moto_on(void);
int hongwai(void);
void xiajiang(void);
void shangshen(void);
void lunzi(void);
void tinzhi(void);

void zhuazi1(void);
void zhuaquqian(void);
void zhuaquhou(void);
void zhuaqutin(void);
#endif



