#ifndef    __key_H
#define    __key_H

#include "hal_data.h"
 
/*********   参数宏定义     *********/
#define   s1                     BSP_IO_PORT_00_PIN_04
#define   s1_down                1
#define   s1_up                  0
#define   s1_Double_click        1
#define   s1_NoDouble_click      0
/*********   函数宏定义     *********/   

//暂无

/*********   函数声明      *********/
uint8_t KEY_Scan(uint8_t mode);

#endif