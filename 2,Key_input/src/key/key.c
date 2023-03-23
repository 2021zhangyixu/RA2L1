#include "key.h"

static uint8_t read_key(void);

/*函数说明：按键扫描
 *传入参数：
		* s1_Double_click ：表示支持连按
		* s1_NoDouble_click ：不支持连按
 *返回参数：
		* s1_down ：表示s1被按下
		* s1_up ：  表示s1没有被按下
 */
uint8_t KEY_Scan(uint8_t mode)
{
	static uint8_t S1_up=1;//按键按松开标志
	if(mode) S1_up=1;  //mode=1表示支持连按	
	if(S1_up && read_key())
	{
		R_BSP_SoftwareDelay(20,BSP_DELAY_UNITS_MILLISECONDS);//延时20ms软件消抖
		S1_up=0;
		if(read_key()) return s1_down;
	}
	else if(!read_key()) S1_up=1;//松手了，即使是松手时候造成的抖动，也表示松手了
	return s1_up;
}

/*函数说明：读取S1引脚的电平
 *传入参数：无
 *返回参数：
		* s1_down ：表示按键按下
		* s1_up ：  表示松手
 */
static uint8_t read_key(void)
{
	bsp_io_level_t S1;
	R_IOPORT_PinRead(&g_ioport_ctrl,s1,&S1);
	if(S1 == BSP_IO_LEVEL_LOW) return s1_down;
	else return s1_up;  
}



