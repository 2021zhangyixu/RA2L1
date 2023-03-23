#include "led.h"

/*����˵����LED��ת��ƽ
 *���������
		* LED1 :��ʾLED1���з�ת
		* LED2 :��ʾLED2���з�ת
 *���ز�������
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


