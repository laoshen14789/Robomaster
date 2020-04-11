#include "bsp_uart.h"
int j=0,k=0;
int vvv;
unsigned char rx[10];
char x[8],y[8];
int X,Y;
void uartinit(){
	__HAL_UART_CLEAR_IDLEFLAG(&huart6);
	__HAL_UART_ENABLE_IT(&huart6, UART_IT_IDLE);
	uart_receive_dma_no_it(&huart6,rx,sizeof(rx));
	
}
static void uart_rx_idle_callback(UART_HandleTypeDef* huart){
	int angle_x,angle_y;
	  //if(uart_receive_dma_no_it(&huart6,rx,sizeof(rx))==HAL_OK){
			//printf("%s",rx);
		 // memset(rx,0,sizeof(rx)+2);
	if(huart == &huart6){
	__HAL_DMA_DISABLE(huart->hdmarx);
		  for(int i=0;i<10;i++){
				  x[i]=rx[i];
			  if(rx[i+1]=='$') {
				  j=i+2;
				  sscanf(x,"%d",&X);
			  }
			  //printf("%d\n",X);
			  if(rx[i+1]=='#'){
				  for(int l=0;l<i;l++){
					  y[l]=rx[j];
					  j++; 
				  }
				  j=0;
				  sscanf(y,"%d",&Y);
			  }
		  }
		 // printf("%d\n",X);
		  //printf("%d\n",X);

	  
		  angle_x=X/6.82;
		  angle_y=Y/6.82;
			vvv=X;
		  //printf("%d\n",angle_x);
		  //printf("%d\n",*angle_y);
			//printf("%s\n",rx);
		__HAL_DMA_SET_COUNTER(huart->hdmarx, sizeof(rx));
		__HAL_DMA_ENABLE(huart->hdmarx);
		  }

	  
	  }

static int uart_receive_dma_no_it(UART_HandleTypeDef* huart, uint8_t* pData, uint32_t Size)
{
  uint32_t tmp1 = 0;

  tmp1 = huart->RxState;
	
	if (tmp1 == HAL_UART_STATE_READY)
	{
		if ((pData == NULL) || (Size == 0))
		{
			return HAL_ERROR;
		}

		huart->pRxBuffPtr = pData;
		huart->RxXferSize = Size;
		huart->ErrorCode  = HAL_UART_ERROR_NONE;

		/* Enable the DMA Stream */
		HAL_DMA_Start(huart->hdmarx, (uint32_t)&huart->Instance->DR, (uint32_t)pData, Size);

		/* 
		 * Enable the DMA transfer for the receiver request by setting the DMAR bit
		 * in the UART CR3 register 
		 */
		SET_BIT(huart->Instance->CR3, USART_CR3_DMAR);

		return HAL_OK;
	}
	else
	{
		return HAL_BUSY;
	}
}
