#include "config.h"
//#include "oled.h"
//#include "nrf_OLED.h"
//#include "lcd_drive.h"
#include "gui.h"

/****************************************************************************
* 名称：GUI_Initialize()
* 功能：初始化GUI，包括初始化显示缓冲区，初始化LCM并清屏。
* 入口参数：无
* 出口参数：无
* 说明：用户根据LCM的实际情况编写此函数。
****************************************************************************/
void  GUI_Initialize(void)
{
    //OLED_Init();//OLED初始化
	//tft_init();
}
/****************************************************************************
* 名称：GUI_FillSCR()
* 功能：全屏填充。直接使用数据填充显示缓冲区。
* 入口参数：dat     填充的数据
* 出口参数：无
* 说明：用户根据LCM的实际情况编写此函数。
****************************************************************************/
void  GUI_FillSCR(TCOLOR dat)
{
	//OLED_Fill(0,0,127,63,dat);
	//OLED_Fill(dat);
	//tft_clear_screen(dat);
	
}
/****************************************************************************
* 名称：GUI_ClearSCR()
* 功能：清屏。
* 入口参数：无
* 出口参数：无
* 说明：用户根据LCM的实际情况编写此函数。
****************************************************************************/
void  GUI_ClearSCR()
{
	
	//OLED_CLS();
	//OLED_CLS_SF();
	//tft_clear_screen(WHITE);
}
/****************************************************************************
* 名称：GUI_Point()
* 功能：在指定位置上画点。
* 入口参数： x      指定点所在列的位置
*            y      指定点所在行的位置
*            color  显示颜色(对于黑白色LCM，为0时灭，为1时显示)
* 出口参数：返回值为1时表示操作成功，为0时表示操作失败。(操作失败原因是指定地址超出有
*          效范围)
* 说明：用户根据LCM的实际情况编写此函数。
****************************************************************************/
void  GUI_Point(uint16 x, uint8 y, TCOLOR color)
{
//GUI_Dot(x,y,color);
	//SetDot_FS(x,y,color);
}
/****************************************************************************
* 名称：GUI_ReadPoint()
* 功能：读取指定点的颜色。
* 入口参数：x       指定点所在列的位置
*           y       指定点所在行的位置
*           ret     保存颜色值的指针
* 出口参数：返回0表示指定地址超出缓冲区范围
* 说明：对于单色，设置ret的d0位为1或0，4级灰度则为d0、d1有效，8位RGB则d0--d7有效，
*      RGB结构则R、G、B变量有效。
****************************************************************************/
uint8  GUI_ReadPoint(uint16 x, uint8 y, TCOLOR *ret)
{//unsigned char ch;
//	ch=GetDot_FS(x,y);
//	return ch;
	return 0;
}
/****************************************************************************
* 名称：GUI_HLine()
* 功能：画水平线。
* 入口参数： x0     水平线起点所在列的位置
*           y0      水平线起点所在行的位置
*           x1      水平线终点所在列的位置
*           color   显示颜色(对于黑白色LCM，为0时灭，为1时显示)
* 出口参数：无
* 说明：对于单色、4级灰度的液晶，可通过修改此函数作图提高速度，如单色LCM，可以一次更
*      新8个点，而不需要一个点一个点的写到LCM中。
****************************************************************************/
void  GUI_HLine(uint16 x0, uint8 y0, uint16 x1, TCOLOR color)
{
    uint8  temp;
    if(x0>x1)               // 对x0、x1大小进行排列，以便画图
    {
        temp = x1;
        x1 = x0;
        x0 = temp;
    }
    do
    {
        GUI_Point(x0, y0, color);   // 逐点显示，描出垂直线
        x0++;
    }
    while(x1>=x0);
}
/****************************************************************************
* 名称：GUI_RLine()
* 功能：画垂直线。
* 入口参数： x0     垂直线起点所在列的位置
*           y0      垂直线起点所在行的位置
*           y1      垂直线终点所在行的位置
*           color   显示颜色
* 出口参数：无
* 说明：对于单色、4级灰度的液晶，可通过修改此函数作图提高速度，如单色LCM，可以一次更
*      新8个点，而不需要一个点一个点的写到LCM中。
****************************************************************************/
void  GUI_RLine(uint16 x0, uint8 y0, uint8 y1, TCOLOR color)
{
    uint8  temp;
    if(y0>y1)       // 对y0、y1大小进行排列，以便画图
    {
        temp = y1;
        y1 = y0;
        y0 = temp;
    }
    do
    {
        GUI_Point(x0, y0, color);   // 逐点显示，描出垂直线
        y0++;
    }
    while(y1>=y0);
}
/****************************************************************************
* 名称：GUI_Exec()
* 功能：刷新屏幕          
*           
*           
* 
* 
* 
****************************************************************************/
void  GUI_Exec(void)
{
	//OLED_Refresh_Gram();
	//OLED_Screen_display();
}


