#include "led.h"

/*����˵����led1��˸
 *�����������
 *���ز�������
 */
void led_1_flicker(void)
{
			LED1_lighting_up;
			R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_SECONDS);
			LED1_lighting_off;
			R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_SECONDS);
}

/*����˵����led2��˸
 *�����������
 *���ز�������
 */
void led_2_flicker(void)
{
			LED2_lighting_up;
			R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_SECONDS);
			LED2_lighting_off;
			R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_SECONDS);
}


