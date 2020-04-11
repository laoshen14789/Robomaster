/**
 ***************************************(C) COPYRIGHT 2018 DJI***************************************
 * @file       display.h
 * @brief      
 * @note         
 * @Version    V1.0.0
 * @Date       Jan-28-2018      
 ***************************************(C) COPYRIGHT 2018 DJI***************************************
 */

#ifndef __DISPLAY__H 
#define __DISPLAY__H

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "oled.h"
#include "bsp_uart.h"

extern void Tell_the_FUCKING_Graphic_Card_TO_Display(void);
void Display_Task(void const * argument);
void display_imu(void const * argument);

#endif
