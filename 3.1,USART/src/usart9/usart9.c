#include "usart9.h"


/*作用：串口9初始化，P109--TXD,P110--RXD
 *传入参数：无
 *返回参数：无
*/
void UART9_Init(void)
{	
	fsp_err_t err = FSP_SUCCESS;
	
	err = R_SCI_UART_Open(&g_uart9_ctrl,&g_uart9_cfg);
	
	assert(err == FSP_SUCCESS);
	
}


volatile bool uart_send_complete_flag = false;          // 发送完成标志
uint8_t USART_RX_BUF[USART_REC_LEN] = First_String;     //接收缓冲,最大USART_REC_LEN个字节.起始字符串为First_String的宏定义

/*

	=============================================================================================================
                                              USART_RX_STA  
  =============================================================================================================
         bit15                     |             bit14                        |         bit13--bit0
  =============================================================================================================
    接收完成标志位（0x0A,换行键）  |         接收到0x0d（回车键）             |     接收到的有效数据个数                                  
  =============================================================================================================

*/
uint16_t USART_RX_STA = First_String_num;       //接收状态标记，根据起始字符串来初始化起始字符位置

void UART_Agreement(uart_callback_args_t * p_args); //串口通讯协议

/*用于串口9的接收和发送中断
 *传入参数：
		*p_args：这个不需要我们管，系统自动会将数据传入
 *返回参数：无
*/
void UART9_callback(uart_callback_args_t * p_args)
{
	switch (p_args->event)
	{
		//如果是串口接收中断
		case UART_EVENT_RX_CHAR:
		{
			UART_Agreement(p_args);//串口通讯协议判断
			if(USART_RX_STA&0x8000)//如果接收完成
			{
				USART_RX_BUF[USART_RX_STA&0x3FFF] = 0x0d;//将字符串自动换行
				USART_RX_STA++;                          //因为增加了0x0d，所以字符串数量+1
				R_SCI_UART_Write(&g_uart9_ctrl, (uint8_t*)USART_RX_BUF, USART_RX_STA&0x3fff);//将字符串数据输出
				USART_RX_STA=First_String_num;                          //将USART_RX_STA初始化
			}
			break;
		}
		//如果是串口发送中断
		case UART_EVENT_TX_COMPLETE:
		{
			uart_send_complete_flag = true;
			break;
		}
		default:
		break;
	}
}

/*用于串口通讯协议判断
 *传入参数：
		*p_args：这个不需要我们管，系统自动会将数据传入
 *返回参数：无
*/
void UART_Agreement(uart_callback_args_t * p_args)
{
	if((USART_RX_STA&0x8000)==0)                                    //bit15没有被置为1，接收未完成
	{
		if(USART_RX_STA&0x4000)                                       //bit14被置为1，表示接收到了'\n'（0x0d）
		{
			if((p_args->data)!=0x0a)USART_RX_STA=0;                     //如果bit14被置1了，但是bit15并不是换行操作，表示接收错误,重新开始
			else USART_RX_STA|=0x8000;	                                //接收完成了 
		}
		else //还没收到'\n'（0x0d）
		{	
			if((p_args->data)==0x0d)USART_RX_STA|=0x4000;               //如果接收到了'\n'（0x0d），bit14被置为1
			else
			{
				USART_RX_BUF[USART_RX_STA&0x3FFF]=(uint8_t)(p_args->data);//如果没有接收到结束标志，继续将数据写入USART_RX_BUF[]
				USART_RX_STA++;
				if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;         //如果接收到的数据大于定义最大接收字节数，表示接收数据错误,重新开始接收	  
			}		 
		}
	} 
}

/* 重定向 printf 输出 */
#if defined __GNUC__ && !defined __clang__
int _write(int fd, char *pBuffer, int size); //防止编译警告
int _write(int fd, char *pBuffer, int size)
{
	(void)fd;
	R_SCI_UART_Write(&g_uartx_ctrl, (uint8_t *)pBuffer, (uint32_t)size);
	while(uart_send_complete_flag == false);
	uart_send_complete_flag = false;
	return size;
}
#else
int fputc(int ch, FILE *f)
{
	(void)f;
	R_SCI_UART_Write(&g_uartx_ctrl, (uint8_t *)&ch, 1);
	while(uart_send_complete_flag == false);
	uart_send_complete_flag = false;
	return ch;
}
#endif

