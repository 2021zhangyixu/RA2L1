#ifndef    __usart9_H
#define    __usart9_H

#include "hal_data.h"
#include <stdio.h>

/*********   参数宏定义     *********/
#define USART_REC_LEN  			50  	                //定义最大接收字节数 50
#define First_String  			"Receive:"            //返回给PC端的起始字符串
#define First_String_num    strlen(First_String)  //起始字符串长度
#define g_uartx_ctrl        g_uart9_ctrl          //如果是串口9需要printf重映射，就写g_uart9_ctrl

/*********   函数宏定义     *********/


/*********   函数声明      *********/
void UART9_Init(void);

#endif