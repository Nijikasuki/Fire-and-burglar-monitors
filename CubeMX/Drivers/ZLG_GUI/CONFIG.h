#ifndef __CONFIG_H
#define __CONFIG_H

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
typedef unsigned char  uint8;                   /* defined for unsigned 8-bits integer variable 	无符号8位整型变量  */
typedef signed   char  int8;                    /* defined for signed 8-bits integer variable		有符号8位整型变量  */
typedef unsigned short uint16;                  /* defined for unsigned 16-bits integer variable 	无符号16位整型变量 */
typedef signed   short int16;                   /* defined for signed 16-bits integer variable 		有符号16位整型变量 */
typedef unsigned int   uint32;                  /* defined for unsigned 32-bits integer variable 	无符号32位整型变量 */
typedef signed   int   int32;                   /* defined for signed 32-bits integer variable 		有符号32位整型变量 */
typedef float          fp32;                    /* single precision floating point variable (32bits) 单精度浮点数（32位长度） */
typedef double         fp64;                    /* double precision floating point variable (64bits) 双精度浮点数（64位长度） */

#include	"LCMDRV.H"
#include	"FONT_MACRO.H"
#include    "GUI_CONFIG.H"
#include    "GUI_BASIC.H"
#include    "GUI_STOCKC.H"
#include    "FONT5_7.H"
#include    "FONT8_8.H"
#include    "FONT24_32.H"
#include    "LOADBIT.H"
#include    "WINDOWS.H"
#include    "MENU.H"
#include    "spline.H"
#include    "ConvertColor.H"


#endif
