#ifndef __KEYSCAN_H__
#define __KEYSCAN_H__

#include "stm32f4xx_hal.h"
#include "remotecontrol.h"
#include "tim.h"

typedef enum
{

	KEY_OFF_UP = 0x01,
	KEY_OFF_MD = 0x02,
	KEY_OFF_DN = 0x03,
	
	KEY_CL_UP = 0x04,
	KEY_CL_MD = 0x05,
	KEY_CL_DN = 0x06,
	
	KEY_HL_UP = 0x07,
	KEY_HL_MD = 0x08,
	KEY_HL_DN = 0x09,
	
}KEY_STATE;

void key_scan(void);
void keycheck(void);

extern rc_info_t rc;
extern uint8_t keystate;

#endif 
