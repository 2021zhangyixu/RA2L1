#ifndef    __usart9_H
#define    __usart9_H

#include "hal_data.h"
#include <stdio.h>

/*********   �����궨��     *********/
#define USART_REC_LEN  			50  	                //�����������ֽ��� 50
#define First_String  			"Receive:"            //���ظ�PC�˵���ʼ�ַ���
#define First_String_num    strlen(First_String)  //��ʼ�ַ�������
#define g_uartx_ctrl        g_uart9_ctrl          //����Ǵ���9��Ҫprintf��ӳ�䣬��дg_uart9_ctrl

/*********   �����궨��     *********/


/*********   ��������      *********/
void UART9_Init(void);

#endif