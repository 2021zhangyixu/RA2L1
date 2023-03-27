#include "led.h"

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


