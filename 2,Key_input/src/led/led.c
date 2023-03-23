#include "led.h"

/*函数说明：LED翻转电平
 *传入参数：
		* LED1 :表示LED1进行翻转
		* LED2 :表示LED2进行翻转
 *返回参数：无
 */
void led_flip(uint16_t led)
{
	if(led == LED1)
	{
		static uint8_t led1_flag = 0;
		led1_flag = !led1_flag;
		R_IOPORT_PinWrite(&g_ioport_ctrl,LED1,led1_flag);
	}
	if(led == LED2)
	{
		static uint8_t led2_flag = 0;
		led2_flag = !led2_flag;
		R_IOPORT_PinWrite(&g_ioport_ctrl,LED2,led2_flag);
	}
}

/*函数说明：led1闪烁
 *传入参数：无
 *返回参数：无
 */
void led_1_flicker(void)
{
			LED1_lighting_up;
			R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_SECONDS);
			LED1_lighting_off;
			R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_SECONDS);
}

/*函数说明：led2闪烁
 *传入参数：无
 *返回参数：无
 */
void led_2_flicker(void)
{
			LED2_lighting_up;
			R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_SECONDS);
			LED2_lighting_off;
			R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_SECONDS);
}


