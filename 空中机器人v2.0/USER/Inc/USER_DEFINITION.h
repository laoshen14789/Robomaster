/**
  ******************************************************************************
  * File Name          : USER_DEFINITION.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2019 TJUT_RoboMaster
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USER_DEFINITION_H
#define __USER_DEFINITION_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

#define CAN_CONTROL	//const current control 
//#define PWM_CONTROL	//const speed control

#define CHASSIS_KP 1.5f
#define CHASSIS_KI 0.1f
#define CHASSIS_KD 0.0f

#define GIMBAL_YAW_KP  50
#define GIMBAL_YAW_KI 5
#define GIMBAL_YAW_KD  30

#define GIMBAL_PIT_KP  100.0f
#define GIMBAL_PIT_KI -40.0f
#define GIMBAL_PIT_KD  230.0f

#define YAW_CORRECTING_ANGLE 7345
#define PIT_CORRECTING_ANGLE 0

#define YAW_OFFSET_ANGLE 0
#define PIT_OFFSET_ANGLE 0

#define POKE_TIM_STRUCT  htim2
#define POKE_TIM_CHANNEL1 TIM_CHANNEL_1
#define POKE_TIM_CHANNEL2 TIM_CHANNEL_2

#define LASER_ON  HAL_GPIO_WritePin(LASER_GPIO_Port, LASER_Pin, GPIO_PIN_SET);
#define LASER_OFF HAL_GPIO_WritePin(LASER_GPIO_Port, LASER_Pin, GPIO_PIN_RESET);


/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MXCONSTANT_H */
/************************ (C) COPYRIGHT TJUT_RoboMaster *****END OF FILE****/
