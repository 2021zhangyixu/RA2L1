#include "usart9.h"


/*���ã�����9��ʼ����P109--TXD,P110--RXD
 *�����������
 *���ز�������
*/
void UART9_Init(void)
{	
	fsp_err_t err = FSP_SUCCESS;
	
	err = R_SCI_UART_Open(&g_uart9_ctrl,&g_uart9_cfg);
	
	assert(err == FSP_SUCCESS);
	
}


volatile bool uart_send_complete_flag = false;          // ������ɱ�־
uint8_t USART_RX_BUF[USART_REC_LEN] = First_String;     //���ջ���,���USART_REC_LEN���ֽ�.��ʼ�ַ���ΪFirst_String�ĺ궨��

/*

	=============================================================================================================
                                              USART_RX_STA  
  =============================================================================================================
         bit15                     |             bit14                        |         bit13--bit0
  =============================================================================================================
    ������ɱ�־λ��0x0A,���м���  |         ���յ�0x0d���س�����             |     ���յ�����Ч���ݸ���                                  
  =============================================================================================================

*/
uint16_t USART_RX_STA = First_String_num;       //����״̬��ǣ�������ʼ�ַ�������ʼ����ʼ�ַ�λ��

void UART_Agreement(uart_callback_args_t * p_args); //����ͨѶЭ��

/*���ڴ���9�Ľ��պͷ����ж�
 *���������
		*p_args���������Ҫ���ǹܣ�ϵͳ�Զ��Ὣ���ݴ���
 *���ز�������
*/
void UART9_callback(uart_callback_args_t * p_args)
{
	switch (p_args->event)
	{
		//����Ǵ��ڽ����ж�
		case UART_EVENT_RX_CHAR:
		{
			UART_Agreement(p_args);//����ͨѶЭ���ж�
			if(USART_RX_STA&0x8000)//����������
			{
				USART_RX_BUF[USART_RX_STA&0x3FFF] = 0x0d;//���ַ����Զ�����
				USART_RX_STA++;                          //��Ϊ������0x0d�������ַ�������+1
				R_SCI_UART_Write(&g_uart9_ctrl, (uint8_t*)USART_RX_BUF, USART_RX_STA&0x3fff);//���ַ����������
				USART_RX_STA=First_String_num;                          //��USART_RX_STA��ʼ��
			}
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

/*���ڴ���ͨѶЭ���ж�
 *���������
		*p_args���������Ҫ���ǹܣ�ϵͳ�Զ��Ὣ���ݴ���
 *���ز�������
*/
void UART_Agreement(uart_callback_args_t * p_args)
{
	if((USART_RX_STA&0x8000)==0)                                    //bit15û�б���Ϊ1������δ���
	{
		if(USART_RX_STA&0x4000)                                       //bit14����Ϊ1����ʾ���յ���'\n'��0x0d��
		{
			if((p_args->data)!=0x0a)USART_RX_STA=0;                     //���bit14����1�ˣ�����bit15�����ǻ��в�������ʾ���մ���,���¿�ʼ
			else USART_RX_STA|=0x8000;	                                //��������� 
		}
		else //��û�յ�'\n'��0x0d��
		{	
			if((p_args->data)==0x0d)USART_RX_STA|=0x4000;               //������յ���'\n'��0x0d����bit14����Ϊ1
			else
			{
				USART_RX_BUF[USART_RX_STA&0x3FFF]=(uint8_t)(p_args->data);//���û�н��յ�������־������������д��USART_RX_BUF[]
				USART_RX_STA++;
				if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;         //������յ������ݴ��ڶ����������ֽ�������ʾ�������ݴ���,���¿�ʼ����	  
			}		 
		}
	} 
}

/* �ض��� printf ��� */
#if defined __GNUC__ && !defined __clang__
int _write(int fd, char *pBuffer, int size); //��ֹ���뾯��
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

