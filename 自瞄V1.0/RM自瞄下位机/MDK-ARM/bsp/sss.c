#include "stdio.h"
#include "stm32f4xx_hal.h"

//�������������.c�ļ������
extern UART_HandleTypeDef huart6;
extern UART_HandleTypeDef huart6;
uint8_t ch;
uint8_t ch_r;
//��д�������,�ض���printf���������ڣ���˼����˵printfֱ����������ڣ���Ĭ�����������̨��
/*fputc*/
int fputc(int c, FILE * f)
{
    ch=c;
   // HAL_UART_Transmit(&huart6,&ch,sizeof(ch),1000);//���ʹ���
    HAL_UART_Transmit(&huart6,&ch,sizeof(ch),100);//���ʹ���
	return c;
}



//�ض���scanf���������� ��˼����˵���ܴ��ڷ����������ݣ���Ĭ���ǽ��ܿ���̨������
/*fgetc*/
int fgetc(FILE * F)    
{
    HAL_UART_Receive_DMA(&huart6,&ch_r,sizeof(ch));//����
    return ch_r;
}
