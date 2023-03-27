#include "usart9.h"



void UART9_Init(void)
{	
	fsp_err_t err = FSP_SUCCESS;
	
	err = R_SCI_UART_Open(&g_uart9_ctrl,&g_uart9_cfg);
	
	assert(err == FSP_SUCCESS);
	
}

// ������ɱ�־
volatile bool uart_send_complete_flag = false;
//char* Debug_String = "Receive:";

void UART9_callback(uart_callback_args_t * p_args)
{
	switch (p_args->event)
	{
		//����Ǵ��ڽ����ж�
		case UART_EVENT_RX_CHAR:
		{
			/* �Ѵ��ڽ��յ������ݷ��ͻ�ȥ */
			R_SCI_UART_Write(&g_uart9_ctrl, (uint8_t *)&(p_args->data), 1);
			break;
		}
		//����Ǵ��ڷ����ж�
		case UART_EVENT_TX_COMPLETE:
		{
			uart_send_complete_flag = true;
			break;
		}
		default:
		break;
	}
}
	
/* �ض��� printf ��� */
#if defined __GNUC__ && !defined __clang__
int _write(int fd, char *pBuffer, int size); //��ֹ���뾯��
int _write(int fd, char *pBuffer, int size)
{
	(void)fd;
	R_SCI_UART_Write(&g_uart9_ctrl, (uint8_t *)pBuffer, (uint32_t)size);
	while(uart_send_complete_flag == false);
	uart_send_complete_flag = false;
	return size;
}
#else
int fputc(int ch, FILE *f)
{
	(void)f;
	R_SCI_UART_Write(&g_uart9_ctrl, (uint8_t *)&ch, 1);
	while(uart_send_complete_flag == false);
	uart_send_complete_flag = false;
	return ch;
}
#endif

