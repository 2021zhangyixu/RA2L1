#include "key.h"

static uint8_t read_key(void);

/*����˵��������ɨ��
 *���������
		* s1_Double_click ����ʾ֧������
		* s1_NoDouble_click ����֧������
 *���ز�����
		* s1_down ����ʾs1������
		* s1_up ��  ��ʾs1û�б�����
 */
uint8_t KEY_Scan(uint8_t mode)
{
	static uint8_t S1_up=1;//�������ɿ���־
	if(mode) S1_up=1;  //mode=1��ʾ֧������	
	if(S1_up && read_key())
	{
		R_BSP_SoftwareDelay(20,BSP_DELAY_UNITS_MILLISECONDS);//��ʱ20ms�������
		S1_up=0;
		if(read_key()) return s1_down;
	}
	else if(!read_key()) S1_up=1;//�����ˣ���ʹ������ʱ����ɵĶ�����Ҳ��ʾ������
	return s1_up;
}

/*����˵������ȡS1���ŵĵ�ƽ
 *�����������
 *���ز�����
		* s1_down ����ʾ��������
		* s1_up ��  ��ʾ����
 */
static uint8_t read_key(void)
{
	bsp_io_level_t S1;
	R_IOPORT_PinRead(&g_ioport_ctrl,s1,&S1);
	if(S1 == BSP_IO_LEVEL_LOW) return s1_down;
	else return s1_up;  
}



