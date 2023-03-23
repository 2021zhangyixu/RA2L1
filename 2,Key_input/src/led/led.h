#ifndef    __led_H
#define    __led_H

#include "hal_data.h"

/*********   参数宏定义     *********/
#define LED1 BSP_IO_PORT_05_PIN_02
#define LED2 BSP_IO_PORT_05_PIN_01

/*********   函数宏定义     *********/
#define LED1_lighting_off    R_IOPORT_PinWrite(&g_ioport_ctrl,LED1,BSP_IO_LEVEL_LOW)
#define LED1_lighting_up     R_IOPORT_PinWrite(&g_ioport_ctrl,LED1,BSP_IO_LEVEL_HIGH)
#define LED2_lighting_off    R_IOPORT_PinWrite(&g_ioport_ctrl,LED2,BSP_IO_LEVEL_LOW)
#define LED2_lighting_up     R_IOPORT_PinWrite(&g_ioport_ctrl,LED2,BSP_IO_LEVEL_HIGH)

/*********   函数声明      *********/
void led_flip(uint16_t led);
void led_1_flicker(void);
void led_2_flicker(void);

#endif



