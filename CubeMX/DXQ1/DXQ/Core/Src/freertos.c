/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gpio.h"
#include "GUI.h"
#include "tim.h"
#include "DS_18B20.h"
#include "MPU6050.h"
#include "Display_3D.h"
#include "ESP01.h"
#include "w25qxx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct { 
	int maxtemp;	// 温度上限（0~90）℃
	int senlevl;	// 震动灵敏度（0~9）
	int warnlen;	// 报警时长（0~60）秒
	int upstep;		// 上传时间间隔（100~10000）ms
	uint8_t chk;	// 校验码
} PARA_SYS;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
extern GUI_FLASH const GUI_FONT GUI_FontHZ_KaiTi_20;
extern GUI_FLASH const GUI_FONT GUI_FontHZ_KaiTi_16;
extern GUI_FLASH const GUI_FONT GUI_FontHZ_KaiTi_12;
extern GUI_CONST_STORAGE GUI_BITMAP bmdy;
extern GUI_CONST_STORAGE GUI_BITMAP bmly;

PARA_SYS g_set = {
	30, 5, 30, 1000
};	// 系统参数设置
int g_setidx = 0;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
#define WS_LOGO 0
#define WS_GUI1 1
#define WS_GUI2 2
#define WS_GUI3 3
#define WS_GUI4 4

int g_ws = WS_LOGO;
uint32_t intick = 0;

volatile float temp = 0;
//float tempLmt = 32.0f;

uint32_t beeptick = 0;
uint8_t tempwarn = 0;
uint8_t mpuwarn = 0;

uint8_t pageidx = 0;
uint32_t warntick = 0;

uint8_t g_bupting = 0;	// 上传开关
//uint32_t g_nupstep = 100;		// 上传时间间隔0.1s

#define MAX_DATALEN 80

float vTemp[MAX_DATALEN];
int cTemp = 0;
float vPitch[MAX_DATALEN];
int cPitch = 0;
float vRoll[MAX_DATALEN];
int cRoll = 0;
float vYaw[MAX_DATALEN];
int cYaw = 0;

unsigned char TAB_Hang[128] = {	/* 杭 0xbabc*/
________,________,________,________,
________,________,________,________,
______XX,X_______,___XX___,________,
______XX,X_______,__XXX___,________,
______XX,X_______,___XXX__,________,
______XX,X_______,___XXXX_,________,
______XX,X_______,____XX__,________,
______XX,X____XXX,XXXXXXXX,XXXXX___,
______XX,X____XXX,XXXXXXXX,XXXXXX__,
__XXXXXX,XXXX_XXX,XXXXXXXX,XXXXXX__,
__XXXXXX,XXXX____,________,________,
______XX,X_______,________,________,
______XX,X_______,________,________,
_____XXX,X______X,XXXXXXXX,XX______,
_____XXX,XXX____X,XXXXXXXX,XX______,
____XXXX,XXX____X,XX_____X,XX______,
____XXXX,XXXX___X,XX_____X,XX______,
____XXXX,XXXX___X,XX_____X,XX______,
___XXXXX,X_XXX__X,XX_____X,XX______,
__XXXXXX,X_XX___X,XX_____X,XX______,
__XXX_XX,X______X,XX_____X,XX______,
_XXX__XX,X______X,XX_____X,XX______,
__XX__XX,X______X,XX_____X,XX______,
______XX,X______X,XX_____X,XX______,
______XX,X______X,X______X,XX______,
______XX,X_____XX,X______X,XX__XX__,
______XX,X____XXX,X______X,XX__XXX_,
______XX,X___XXXX,_______X,XX__XXX_,
______XX,X__XXXX_,_______X,XXXXXXX_,
______XX,X_XXXX__,________,XXXXXX__,
______XX,X___X___,________,________,
________,________,________,________
};

/* USER CODE END Variables */
/* Definitions for MainTask */
osThreadId_t MainTaskHandle;
const osThreadAttr_t MainTask_attributes = {
  .name = "MainTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for KeyTask */
osThreadId_t KeyTaskHandle;
const osThreadAttr_t KeyTask_attributes = {
  .name = "KeyTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for UartTask */
osThreadId_t UartTaskHandle;
const osThreadAttr_t UartTask_attributes = {
  .name = "UartTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for GUITask */
osThreadId_t GUITaskHandle;
const osThreadAttr_t GUITask_attributes = {
  .name = "GUITask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for DataTask */
osThreadId_t DataTaskHandle;
const osThreadAttr_t DataTask_attributes = {
  .name = "DataTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void WSLogo(void);
void DrawLogo(void);
void DrawGUI1(void);
void DrawGUI2(void);
void DrawGUI3(void);
void DrawGUI4(void);
void Beep(int time, int tune);
void BeepDone(void);

void DispSeg(uint8_t num[4], uint8_t dot);	

/* USER CODE END FunctionPrototypes */

void StartMainTask(void *argument);
void StartKeyTask(void *argument);
void StartUartTask(void *argument);
void StartGUITask(void *argument);
void StartDataTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of MainTask */
  MainTaskHandle = osThreadNew(StartMainTask, NULL, &MainTask_attributes);

  /* creation of KeyTask */
  KeyTaskHandle = osThreadNew(StartKeyTask, NULL, &KeyTask_attributes);

  /* creation of UartTask */
  UartTaskHandle = osThreadNew(StartUartTask, NULL, &UartTask_attributes);

  /* creation of GUITask */
  GUITaskHandle = osThreadNew(StartGUITask, NULL, &GUITask_attributes);

  /* creation of DataTask */
  DataTaskHandle = osThreadNew(StartDataTask, NULL, &DataTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartMainTask */
/**
  * @brief  Function implementing the MainTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartMainTask */
void StartMainTask(void *argument)
{
  /* USER CODE BEGIN StartMainTask */
	uint8_t num[4] = {0};

  /* Infinite loop */
  for(;;)
  {
		switch (g_ws)
		{
			case WS_LOGO:
				WSLogo();
				break;
			default:
				SetLeds(0);
				break;
		}
		
		num[0] = num[1] = num[2] = num[3] = ' ';
		
		if (osKernelGetTickCount() > intick + 5000)
		{
			if ((tempwarn || mpuwarn) && g_set.warnlen > 0)
			{
				if (0 == warntick)
					warntick = osKernelGetTickCount();
				else if (osKernelGetTickCount() >= warntick + g_set.warnlen * 1000)
				{
					tempwarn = mpuwarn = 0;
					warntick = 0;
				}
				else
				{
					uint32_t tic = warntick + g_set.warnlen * 1000 - osKernelGetTickCount();
					num[0] = (tic / 10000) % 10;
					num[1] = (tic / 1000) % 10;
					num[2] = (tic / 100) % 10;
					num[3] = (tic / 10) % 10;	
					
					if (tempwarn)
					{
						if (num[2] == 1 || num[2] == 3 || num[2] == 5)
							Beep(100, num[2]);
					}
					else if (mpuwarn)
					{
						if (num[2] != 0)
							Beep(100, num[2]);
					}
				}	
			}
			else
				num[0] = num[1] = num[2] = num[3] = ' ';
		}
		
   	DispSeg(num, 2);
		BeepDone();
		
    osDelay(1);
  }
  /* USER CODE END StartMainTask */
}

/* USER CODE BEGIN Header_StartKeyTask */
/**
* @brief Function implementing the KeyTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartKeyTask */
void StartKeyTask(void *argument)
{
	
  /* USER CODE BEGIN StartKeyTask */
  /* Infinite loop */
	uint32_t keytick = 0;
	PARA_SYS set;
		
  for(;;)
  {
		uint8_t key = ScanKey();
		if (key > 0)
			printf("%02X\n", key);
		
		if (g_keysta == (KEY1 | KEY2 | KEY3 | KEY4))
		{
			if (0 == keytick)
				keytick = osKernelGetTickCount();
			else if (osKernelGetTickCount() >= keytick + 3000)
			{
				keytick = 0;
				
				if (g_set.warnlen > 0)
				{
					g_set.warnlen = tempwarn = mpuwarn = 0;
					osDelay(500);
				}
				else
				{
					PARA_SYS set;
					W25QXX_Read((uint8_t *)&set, 0, sizeof(set));
					if ((set.maxtemp >= 0 && set.maxtemp <= 90) &&
							(set.senlevl >= 0 && set.senlevl <= 9)  &&
							(set.warnlen >= 0 && set.warnlen <= 60) &&
							(set.upstep >= 100 && set.upstep <= 10000))
						memcpy(&g_set, &set, sizeof(set));
				}
			}
		}
		else
			keytick = 0;
		
		if (tempwarn || mpuwarn)
			key = 0;
		
		switch (g_ws)
		{
			case WS_LOGO:
				if (KEY5 == key)
				{
					g_ws = WS_GUI1;
					intick = 0;
				}
				else if (KEY6 == key)
					g_ws = WS_LOGO;
				break;
				
			case WS_GUI1:
				if (KEY1 == key)
					g_ws = WS_GUI4;
				else if (KEY4 == key)
					g_ws = WS_GUI2;
				else if (KEY2 == key)
				{
					if (pageidx > 0)
						--pageidx;
				}
				else if (KEY3 == key)
				{
					if (pageidx < 2)
						++pageidx;
				}
				else if (KEY6 == key)
					g_ws = WS_LOGO;
				break;
					
			case WS_GUI2:
				if (KEY1 == key)
					g_ws = WS_GUI1;
				else if (KEY4 == key)
					g_ws = WS_GUI3;
				else if (KEY6 ==	 key)
					g_ws = WS_LOGO;
				else if (KEY2 == key)
				{
					if (pageidx > 0)
						--pageidx;
				}
				else if (KEY3 == key)
				{
					if (pageidx < 4)
						++pageidx;
				}
				break;
				
			case WS_GUI3:
				if (KEY1 == key)
					g_ws = WS_GUI2;
				else if (KEY4 == key)
					g_ws = WS_GUI4;
				else if (KEY6 == key)
					g_ws = WS_LOGO;
				else if (KEY2 == key)
					g_bupting = 1;
				else if (KEY3 == key)
					g_bupting = 0;
				else if (KEY5 == key)
					InitEsp01(&huart6);		// 重新初始化ESP串口并连接服务器
				break;
				
			case WS_GUI4:
				memcpy(&set, &g_set, sizeof(g_set));
				if (KEY1 == key)
					g_ws = WS_GUI3;
				else if (KEY4 == key)
					g_ws = WS_GUI1;
				else if (KEY6 == key)
					g_ws = WS_LOGO;
				else if (KEY5 == key)
				{
					++g_setidx;
					g_setidx %= 4;
				}
				else if (KEY2 == key)
				{
					switch (g_setidx)
					{
						default:  break;
						case 0: if (g_set.maxtemp > 0) --g_set.maxtemp;  break;
						case 1: if (g_set.senlevl > 0) --g_set.senlevl;  break;
						case 2: if (g_set.warnlen > 0) --g_set.warnlen;  break;
						case 3: if (g_set.upstep > 100) g_set.upstep -= 100;  break;	
					}
				}
				else if (KEY3 == key)
				{
					switch (g_setidx)
					{
						default:  break;
						case 0: if (g_set.maxtemp < 90) ++g_set.maxtemp;  break;
						case 1: if (g_set.senlevl < 9)  ++g_set.senlevl;  break;
						case 2: if (g_set.warnlen < 60) ++g_set.warnlen;  break;
						case 3: if (g_set.upstep < 10000) g_set.upstep += 100;  break;	
					}
				}
				
				if (memcmp(&set, &g_set, sizeof(g_set)) != 0)
				{
					printf("Save %d℃, %d, %d秒, %.1f秒\n", g_set.maxtemp, g_set.senlevl, g_set.warnlen, g_set.upstep / 1000.0f);
					W25QXX_Write((uint8_t *)&g_set, 0, sizeof(g_set));
				}
        break;				
		}
    osDelay(1);
  }
  /* USER CODE END StartKeyTask */
}

/* USER CODE BEGIN Header_StartUartTask */
/**
* @brief Function implementing the UartTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartUartTask */
void StartUartTask(void *argument)
	{
  /* USER CODE BEGIN StartUartTask */
  /* Infinite loop */
  for(;;)
  {
		if (EspRxDataOk())
		{
			// 接收数据处理
			if (g_esp01.rxdata.rx_len > 0)
			{
				char *pstr = (char *)(g_esp01.rxdata.rx_buf);
				if (strstr(pstr, "UPON" ) == pstr)
					g_bupting = 1;
				else if (strstr(pstr, "UPOFF") == pstr)
					g_bupting = 0;
				else if (strstr(pstr, "GETPARA") == pstr)
				{
					char upstr[50];
					sprintf(upstr, "P:%d,%d,%d,%d\n", g_set.maxtemp, g_set.senlevl, g_set.warnlen, g_set.upstep);
					SendEspStr(upstr);
				}
				else if (strstr(pstr, "PSET:") == pstr)
				{
					PARA_SYS set;
					char *p = pstr + 5;
					set.maxtemp = atoi(p);
					p = strstr(p, ",");
					if (p > pstr)
					{
						set.senlevl = atoi(p + 1);
						p = strstr(p + 1, ",");
						if (p > pstr)
						{
							set.warnlen = atoi(p + 1);
							p = strstr(p + 1, ",");
							if (p > pstr)
							{
								set.upstep = atoi(p + 1);
								if ((set.maxtemp >= 0 && set.maxtemp <= 90) &&
										(set.senlevl >= 0 && set.senlevl <= 9)  &&
										(set.warnlen >= 0 && set.warnlen <= 60) &&
										(set.upstep >= 100 && set.upstep <= 10000))	
								{
									memcpy(&g_set, &set, sizeof(set));
									printf("Save %d℃, %d, %d秒, %.1f秒\n", g_set.maxtemp, g_set.senlevl, g_set.warnlen, g_set.upstep / 1000.0f);
									W25QXX_Write((uint8_t *)&g_set, 0, sizeof(g_set));
								}
							}
						}
					}
				}
			}	
		}
    osDelay(1);
  }
  /* USER CODE END StartUartTask */
}

/* USER CODE BEGIN Header_StartGUITask */
/**
* @brief Function implementing the GUITask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartGUITask */
void StartGUITask(void *argument)
{
  /* USER CODE BEGIN StartGUITask */
	GUI_Init();
	
  /* Infinite loop */
  for(;;)
  {
		switch (g_ws)     
		{
			case WS_LOGO:  DrawLogo();  break;
			case WS_GUI1:	 DrawGUI1();  break;
			case WS_GUI2:  DrawGUI2();  break;
      case WS_GUI3:	 DrawGUI3();  break;
      case WS_GUI4:	 DrawGUI4();  break;
			default:  
				break;
		}
    osDelay(100);
  }
  /* USER CODE END StartGUITask */
}

/* USER CODE BEGIN Header_StartDataTask */
/**
* @brief Function implementing the DataTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDataTask */
void StartDataTask(void *argument)
{
  /* USER CODE BEGIN StartDataTask */
	osDelay(100);
	
	ds18b20_init();
	
	W25QXX_Init();
	
	PARA_SYS set;
	W25QXX_Read((uint8_t *)&set, 0, sizeof(set));
	if ((set.maxtemp >= 0 && set.maxtemp <= 90) &&
			(set.senlevl >= 0 && set.senlevl <= 9)  &&
		  (set.warnlen >= 0 && set.warnlen <= 60) &&
			(set.upstep >= 100 && set.upstep <= 10000))
	{
		memcpy(&g_set, &set, sizeof(set));
		printf("Load %d℃, %d, %d秒, %.1f秒\n", g_set.maxtemp, g_set.senlevl, g_set.warnlen, g_set.upstep / 1000.0f);
	}
	
	uint8_t mpuok = MPU_init();
	uint8_t cnt = 0;
	while (cnt++ < 3 && !mpuok)
	{
		osDelay(500);
		mpuok =	MPU_init();
	}
	
	InitEsp01(&huart6);		// ESP01串口初始化，该动作不能放到串口任务！
	uint32_t dstick = 0;
	uint32_t mputick = 0;
	uint32_t uptick = 0;
	char upstr[100];
	
	int warncnt = 0;
	
  /* Infinite loop */
  for(;;)
  {
		
			if (osKernelGetTickCount() >= dstick + 1000)
			{
				dstick = osKernelGetTickCount();
				float ft = ds18b20_read();
				if (ft < 125)
				{
					temp = ft;
					if (cTemp < MAX_DATALEN)
						vTemp[cTemp++] = temp;
					else 
					{
						memcpy((void *)vTemp, (void *)(vTemp + 1), sizeof(vTemp[0]) * (MAX_DATALEN - 1));
						vTemp[MAX_DATALEN - 1] = temp;
					}
					
					if (temp >= g_set.maxtemp && g_set.warnlen)
					{
						printf("temp:%.1f\n", temp);
						tempwarn = 1;
	//					warntick = osKernelGetTickCount();
					}
				}
			}	
			
			if (mpuok)
			{
				if (osKernelGetTickCount() >= mputick + 50)
				{
					mputick = osKernelGetTickCount(); 
					MPU_getdata();

					if (cPitch < MAX_DATALEN)
						vPitch[cPitch++] = fAX;
					else 
					{
						memcpy((void *)vPitch, (void *)(vPitch + 1), sizeof(vPitch[0]) * (MAX_DATALEN - 1));
						vPitch[MAX_DATALEN - 1] = fAX;
					}
					if (cRoll < MAX_DATALEN)
						vRoll[cRoll++] = fAY;
					else 
					{
						memcpy((void *)vRoll, (void *)(vRoll + 1), sizeof(vRoll[0]) * (MAX_DATALEN - 1));
						vRoll[MAX_DATALEN - 1] = fAY;
					}
					if (cYaw < MAX_DATALEN)
						vYaw[cYaw++] = fAZ;
					else 
					{
						memcpy((void *)vYaw, (void *)(vYaw + 1), sizeof(vYaw[0]) * (MAX_DATALEN - 1));
						vYaw[MAX_DATALEN - 1] = fAZ;
					}
					
					if ((gx * gx + gy * gy + gz * gz > 2000 * (10 - g_set.senlevl)) && g_set.warnlen)
					{
						if (++warncnt >= 5 && g_set.senlevl > 0)
						{
							mpuwarn = 1;
							printf("axyz:%6d %6d %6d, gxyz:%6d %6d %6d\n", ax, ay, az, gx, gy, gz);
	//						warntick = osKernelGetTickCount();
						}
					}
					else
						warncnt = 0;	
				}
			}
			
			if (g_bupting && g_esp01.bConnect == 3)
			{
				if (osKernelGetTickCount() >= uptick)
				{
					uptick = osKernelGetTickCount() + g_set.upstep;
					sprintf(upstr, "T:%5.1f, A:%6d %6d %6d, G:%6d %6d %6d, F:%6.1f %6.1f %6.1f,	W:%d\n",
									temp, ax, ay, az, gx, gy, gz, fAX, fAY, fAZ, tempwarn + mpuwarn * 2);
					SendEspStr(upstr);
				}
			}				
			osDelay(1);
	
	}
  /* USER CODE END StartDataTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void WSLogo(void)
{
	static uint32_t tick = 0;
	static uint8_t leds_sta = 0x00;
	
	if (0 == intick)
		intick = osKernelGetTickCount();
	else 
	{
		if (osKernelGetTickCount() >= intick + 8000)
		{
			intick = 0;
			g_ws = WS_GUI1;
			Beep(500, 3);
		}		
	}
	
	SetLeds(leds_sta);
	if (osKernelGetTickCount() >= tick + 500)
	{
		leds_sta = ~leds_sta;
		tick = osKernelGetTickCount();
	}
}

void DrawLogo()
{
	static uint32_t tick = 0;
	
	if (0 == intick)
		intick = osKernelGetTickCount();
	else 
	{
		if (osKernelGetTickCount() <= intick + 2000)
		{
			GUI_Clear();
			GUI_SetFont(&GUI_FontHZ_KaiTi_20);
			GUI_DispStringHCenterAt("防火、防盗远\n程监测器设计", 64, 12);
			GUI_Update();
		}		
		else if (osKernelGetTickCount() <= intick + 5000)
		{
			GUI_Clear();
			GUI_SetFont(&GUI_FontHZ_KaiTi_16);
			GUI_DispStringHCenterAt("成员1董言\n21041509",64,0);
			GUI_DispStringHCenterAt("成员2乐熠\n21041516",64,32);
			GUI_Update();
		}
		else if (osKernelGetTickCount() <= intick + 8000)
		{
			GUI_Clear();
			GUI_DrawBitmap(&bmdy, 0, 0);
			GUI_DrawBitmap(&bmly, 64, 0);
			GUI_Update();
		}
		else
			intick = 0;
	}
}

void DrawGUI1(void)
{
	GUI_Clear();
	GUI_SetFont(&GUI_FontHZ_KaiTi_12);
	GUI_SetColor(GUI_COLOR_BLACK);
	GUI_DispStringAt("实时监测", 0, 0);
	GUI_SetColor(GUI_COLOR_WHITE);
	GUI_DispStringAt("数据曲线", 0, 13);
	GUI_DispStringAt("无线通信", 0, 26);
	GUI_DispStringAt("参数设置", 0, 39);
	GUI_DispStringAt("K1︽  K2《  K3》 K4︾", 0, 52);
	
	GUI_DrawHLine(52, 0, 128);
	GUI_DrawVLine(48, 0, 52);
	
	char buf[20];
	
	if (0 == pageidx)
	{
		GUI_DispStringAt("当前温度:", 50, 0);
		GUI_DispStringAt("震动报警:", 50, 26);
		sprintf(buf, "%.1f℃", temp);
		GUI_DispStringAt(buf, 90, 13);
		GUI_DispStringAt(mpuwarn ? "是" : "否", 90, 39);
	}
	else if (1 == pageidx)
	{
		sprintf(buf, "ax:%6d", ax);
		GUI_DispStringAt(buf, 50, 0);
		if (ax > 0)
			GUI_FillRect(70, 13, 70 + ax * 55 / 32768, 16);
		else if (ax < 0)
			GUI_DrawRect(70, 13, 70 - ax * 55 / 32768, 16);
		sprintf(buf, "ay:%6d", ay);
		GUI_DispStringAt(buf, 50, 17);		
		if (ay > 0)
			GUI_FillRect(70, 30, 70 + ay * 55 / 32768, 33);
		else if (ay < 0)
			GUI_DrawRect(70, 30, 70 - ay * 55 / 32768, 33);
		sprintf(buf, "az:%6d", az);
		GUI_DispStringAt(buf, 50, 34);		
		if (az > 0)
			GUI_FillRect(70, 47, 70 + az * 55 / 32768, 50);
		else if (az < 0)
			GUI_DrawRect(70, 47, 70 - az * 55 / 32768, 50);
	}
	else if (2 == pageidx)
	{
		sprintf(buf, "gx:%6d", gx);
		GUI_DispStringAt(buf, 50, 0);
		if (gx > 0)
			GUI_FillRect(70, 13, 70 + gx * 55 / 32768, 16);
		else if (gx < 0)
			GUI_DrawRect(70, 13, 70 - gx * 55 / 32768, 16);
		sprintf(buf, "gy:%6d", gy);
		GUI_DispStringAt(buf, 50, 17);		
		if (gy > 0)
			GUI_FillRect(70, 30, 70 + gy * 55 / 32768, 33);
		else if (gy < 0)
			GUI_DrawRect(70, 30, 70 - gy * 55 / 32768, 33);
		sprintf(buf, "gz:%6d", gz);
		GUI_DispStringAt(buf, 50, 34);		
		if (gz > 0)
			GUI_FillRect(70, 47, 70 + gz * 55 / 32768, 50);
		else if (gz < 0)
			GUI_DrawRect(70, 47, 70 - gz * 55 / 32768, 50);
	}
	GUI_Update();
}	

void DrawGUI2(void)
{
	char buf[20];
	int i;
	
	GUI_Clear();
	GUI_SetFont(&GUI_FontHZ_KaiTi_12);
	GUI_DispStringAt("实时监测", 0, 0);
	GUI_SetColor(GUI_COLOR_BLACK);
	GUI_DispStringAt("数据曲线", 0, 13);
	GUI_SetColor(GUI_COLOR_WHITE);
	GUI_DispStringAt("无线通信", 0, 26);
	GUI_DispStringAt("参数设置", 0, 39);
	GUI_DispStringAt("K1︽  K2《  K3》 K4︾", 0, 52);
	
	GUI_DrawHLine(52, 0, 128);
	GUI_DrawVLine(48, 0, 52);
	int sw = 128 - 48;
	int sh = 64 - 12 - 12;
	int ox = 48;
	int oy = 12 + sh;
	
	switch (pageidx)
	{
		default:
			break;
		case 0:
		{
			float tempMin = 25;
			float tempMax = 35;
			float tempLmt = 30;
			float dh = sh / (tempMax - tempMin);
			sprintf(buf, "温度:%.1f℃", temp);
			GUI_DispStringAt(buf, 50, 0);
			for (i = 0; i < MAX_DATALEN; i += 6)
				GUI_DrawHLine(oy - (g_set.maxtemp - tempMin) * dh, ox + i, ox + i + 3);
			for (i = 1; i < cTemp && i < MAX_DATALEN; ++i)
				GUI_DrawLine(ox + i - 1, oy - (vTemp[i - 1] - tempMin) * dh, ox + i, oy - (vTemp[i] - tempMin) * dh);
		}
			break;
		case 1:
		{
			float tempMin = -90;
			float tempMax = 90;
			float dh = sh / (tempMax - tempMin);
			sprintf(buf, "俯仰角:%.1f°", fAX);
			GUI_DispStringAt(buf, 50, 0);
			GUI_DrawHLine(oy + tempMin * dh, ox, ox + sw);
			
			for (i = 1; i < cPitch && i < MAX_DATALEN; ++i)
				GUI_DrawLine(ox + i - 1, oy - (vPitch[i - 1] - tempMin) * dh, ox + i, oy - (vPitch[i] - tempMin) * dh);
		}
			break;
		case 2:
		{
			float tempMin = -180;
			float tempMax = 180;
			float dh = sh / (tempMax - tempMin);
			sprintf(buf, "横滚角:%.1f°", fAY);
			GUI_DispStringAt(buf, 50, 0);
			GUI_DrawHLine(oy + tempMin * dh, ox, ox + sw);
			
			for (i = 1; i < cRoll && i < MAX_DATALEN; ++i)
				GUI_DrawLine(ox + i - 1, oy - (vRoll[i - 1] - tempMin) * dh, ox + i, oy - (vRoll[i] - tempMin) * dh);
		}
			break;
		case 3:
		{
			float tempMin = -180;
			float tempMax = 180;
			float dh = sh / (tempMax - tempMin);
			sprintf(buf, "航向角:%.1f°", fAZ);
			GUI_DispStringAt(buf, 50, 0);
			GUI_DrawHLine(oy + tempMin * dh, ox, ox + sw);
			
			for (i = 1; i < cYaw && i < MAX_DATALEN; ++i)
				GUI_DrawLine(ox + i - 1, oy - (vYaw[i - 1] - tempMin) * dh, ox + i, oy - (vYaw[i] - tempMin) * dh);
		}
			break;
		case 4:
			ox = (48 + 128) / 2;
			oy = (12 + 40) / 2 + 2;
			RateCube(fAX, fAY, fAZ, GUI_COLOR_WHITE, ox, oy);
//			RotatePic32X32(TAB_Hang, fAX, fAY, fAZ, GUI_COLOR_WHITE, ox - 16, oy - 16);
			break;
	}
	GUI_Update();
}	

void DrawGUI3(void)
{
	char buf[30];
	GUI_Clear();
	GUI_SetFont(&GUI_FontHZ_KaiTi_12);
	GUI_DispStringAt("实时监测", 0, 0);
	GUI_DispStringAt("数据曲线", 0, 13);
	GUI_SetColor(GUI_COLOR_BLACK);
	GUI_DispStringAt("无线通信", 0, 26);
	GUI_SetColor(GUI_COLOR_WHITE);	
	GUI_DispStringAt("参数设置", 0, 39);
	GUI_DispStringAt("K1︽  K2《  K3》 K4︾", 0, 52);
	
	GUI_DispStringAt(g_esp01.bAtOK ? g_esp01.strESPName : "未连接", 50, 0);		//显示ESP模块的SSID
//	GUI_DispStringAt(g_esp01.strAPName, 50, 0);		//显示连接的热点名称（不支持中文）
	GUI_DispStringAt(TCP_SERVER, 50, 13);		//显示连接服务器IP地址
	sprintf(buf, "端口号:%d", TCP_PORT);
	GUI_DispStringAt(buf, 50, 26);		//显示连接服务器TCP端口号
	GUI_DispStringAt((g_esp01.bConnect == 3) ? "OK" : "ERR", 50, 39);		//服务器连接状态
	GUI_DispStringAt(g_bupting ? "上传中" : "未上传", 70, 39);		//上传状态
	
	GUI_DrawHLine(52, 0, 128);
	GUI_DrawVLine(48, 0, 52);
	GUI_Update();
}	

void DrawGUI4(void)
{
	char buf[20];
	
	GUI_Clear();
	GUI_SetFont(&GUI_FontHZ_KaiTi_12);
	GUI_DispStringAt("实时监测", 0, 0);
	GUI_DispStringAt("数据曲线", 0, 13);
	GUI_DispStringAt("无线通信", 0, 26);
	GUI_SetColor(GUI_COLOR_BLACK);
	GUI_DispStringAt("参数设置", 0, 39);
	GUI_SetColor(GUI_COLOR_WHITE);
	GUI_DispStringAt("K1︽  K2《  K3》 K4︾", 0, 52);
	
	GUI_DispStringAt("温度上限：", 50, 0);
	GUI_DispStringAt("震动灵敏度：", 50, 13);
	GUI_DispStringAt("报警时长：", 50, 26);
	GUI_DispStringAt("上传间隔：", 50, 39);
	
	sprintf(buf, "%d℃", g_set.maxtemp);
	GUI_SetColor((0 == g_setidx) ? GUI_COLOR_BLACK : GUI_COLOR_WHITE);
	GUI_DispStringAt(buf, 104, 0);
	
	sprintf(buf, "%d", g_set.senlevl);
	GUI_SetColor((1 == g_setidx) ? GUI_COLOR_BLACK : GUI_COLOR_WHITE);
	GUI_DispStringAt(buf, 116, 13);
	
  sprintf(buf, "%d秒", g_set.warnlen);
	GUI_SetColor((2 == g_setidx) ? GUI_COLOR_BLACK : GUI_COLOR_WHITE);
	GUI_DispStringAt(buf, 104, 26);
	
	sprintf(buf, "%.1fs", g_set.upstep / 1000.0f);
	GUI_SetColor((3 == g_setidx) ? GUI_COLOR_BLACK : GUI_COLOR_WHITE);
	GUI_DispStringAt(buf, 104, 39);
	GUI_SetColor(GUI_COLOR_WHITE);
	
	GUI_DrawHLine(52, 0, 128);
	GUI_DrawVLine(48, 0, 52);
	GUI_Update();
}	

void Beep(int time, int tune)
{
	static uint16_t TAB[] = {494, 523, 588, 660, 698, 784, 880, 988};
	HAL_TIM_Base_Start(&htim3); 
	
	if (tune >= 1 && tune <= 7)
	{
		int pre = 1000000 / TAB[tune];
		__HAL_TIM_SET_AUTORELOAD(&htim3, pre);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pre / 2);
		
		beeptick = osKernelGetTickCount() + time;
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	}
}

void BeepDone(void)
{
	if (beeptick > 0 && osKernelGetTickCount() >= beeptick)
	{
		beeptick = 0;
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
	}
}

void DispSeg(uint8_t num[4], uint8_t dot)
{
	for (int i = 0; i < 4; ++i)
	{
		Write595(i, num[i], (dot == (i + 1)) ? 1 : 0);
		osDelay(1);
	}
}
/* USER CODE END Application */

