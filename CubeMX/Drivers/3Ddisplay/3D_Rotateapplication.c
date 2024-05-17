/*******************************************************************************
* �ĵ�: 3D_Rotateapplitation.c
* ����: ִ��ִս
* 		QQ:572314251
*		΢�ţ�zhinianzhizhan
*		���Σ����ģ���Ը����ִ�Ϊ��ִս��ִս���죡
*
* ����:
*	1.��άͼ�α任����
*       2.3D-transform.c�������任�㷨���͡�ͶӰ�㷨��
*       
*       3.3D_Rotateapplitation�ԡ��任�����㷨���͡�ͶӰ�㷨����Ӧ��
*       4.rotation_font3D.cʵ����ά�ռ�����תͼƬ���Ż��㷨��
*       5.��3D�㷨ѧϰ�ԡ�����STC��Ƭ����12864Һ����ʾ��ת�������ͼƬ���Ż��㷨����ʵ����
*	6.		������Wu LianWei
*	7.���ĵ�Ϊ3D_Rotateapplitation�ԡ��任�����㷨���͡�ͶӰ�㷨����Ӧ��
*	8��ע�⣺�ӵ㵽ƽ��ľ��룬����Ļ�ϵ�����ͼת��ת�����ˣ�
		��ͼ��ɫʱ���Ÿĸ��ӵ㵽����ľ���FOCAL_DISTANCE�������任��������ֵ�Ĵ�С��XO,YO �Ĵ�С
		Ҫȷ��ͼ����ת�����в��ᳬ���߽磬��Ȼ�ͻ�����
	9.����ע���е�240 400��������֮ǰ��240*400����Ļ����ֲʱд�ģ�����ת��Ϊ128   64 �ȣ���Ӱ��
	
******* �����˺������ϣ�������ĵ�����Ϊ�ĸ���//ʱ�䣺2017/2/5
*******
	10.ת��ʹ��ʱ��ע������
*******************************************************************************/



#include <math.h>

#include <Display_3D.h>

#include <GUI.h>
//#include "front.h"
#define WHITE 0
#define BLACK 0xFFFFFF

/**********************************************************/
//**������Retate_cube
//**���ܣ���ת������
//**˵����  1����ת���������3D��ʾ������3Dͼ�α任�㷨��ͶӰ�㷨
//				  
//					 ��ѧ��д
//**���ߣ�  ִ��ִս
///**ʱ�䣺2015-11-30 
/***********************************************************/

#define  SIZE  8

_3Dzuobiao const Cube[8]=		//const �൱��51 �е�code����ʾ�����rom����Ϊֻ��
{																	
	{0,0,0},
	{8,0,0},//��������ı߳��ĳ�һЩ����Ӧ800x480�Ĵ�������Ȼ߯С    2018-12-1 ִ��ִս wcc
	{0,8,0},
	{8,8,0},
	
	{0,0,8},
	{8,0,8},	//ֻ��������������������,�൱�������εı߳�����������һ���������޸ĳ��̣��Լ�9��ɳ����λ�������
	{0,8,8},	//������Щ����û�е���������������Դ˴��޸ĺ���Щ�ط�����ҲҪ��Ӧ�޸ġ���ʵ�ʲ��������޸ġ�
	{8,8,8}	//��arduino����Ϸ���п������л���ά��ת�ɻ��ģ�ԭ����Ӧ��һ�������ɻ��ĸ������������������ǻ��ߵ�˳��
				//�����Ժ���԰���������յ�˳�������ӻ��ߵĺ������Ϳ��Ի������ͼ���ˡ����Ժ��ƻ������޸İ� 2017-2-5
	
 //   {0,0,0},
 //   {8,0,0},
 //   {0,8,0},
 //   {8,8,0},
    
//  {0,0,8},
//	{8,0,8},	//ֻ��������������������,�൱�������εı߳�����������һ���������޸ĳ��̣��Լ�9��ɳ����λ�������
//	{0,8,8},	//������Щ����û�е���������������Դ˴��޸ĺ���Щ�ط�����ҲҪ��Ӧ�޸ġ���ʵ�ʲ��������޸ġ�
//	{8,8,8}	//��arduino����Ϸ���п������л���ά��ת�ɻ��ģ�ԭ����Ӧ��һ�������ɻ��ĸ������������������ǻ��ߵ�˳��
				//�����Ժ���԰���������յ�˳�������ӻ��ߵĺ������Ϳ��Ի������ͼ���ˡ����Ժ��ƻ������޸İ� 2017-2-5
	
//	{-1,-1,-1},
//{1,-1,-1},
//{1,-1,1},
//{-1,-1,1}, 
//{-1, 1,-1},
//{1, 1,-1},
//{1, 1,1},
//{-1, 1,1}
};

_3Dzuobiao const Triangle[3]=
{
	{4,2,0},
	{2,6,0},
	{6,6,0}
};

///**********************************************************/
///**����: Rotate_cube
///**���ܣ���ת������
///**˵����

//					 ��ѧ��д
//**���ߣ�  ִ��ִս
///**ʱ�䣺2015-11-30
//�޸�ʱ�䣺 2017/2/5   23:00
//					���ԭ�����õ��β�
///***********************************************************/

void Rotate_cube(float ax,float ay,float az)   //��ת��������
{	uint8_t i;
		float gMAT[4][4];
	_3Dzuobiao temp;
	_2Dzuobiao Cube_dis[8];
	_2Dzuobiao Triangle_dis[3];
	
	structure_3D(gMAT);         	//����Ϊ��λ����
	Translate3D(gMAT,-4,-4,-4); 	//ƽ�Ʊ任����
	Scale_3D(gMAT,6,6,6);		//�����任����
	Rotate_3D(gMAT,ax,ay,az);	//��ת�任����
	Translate3D(gMAT,4,4,32); 	//ƽ�Ʊ任����	
	
	for(i=0;i<SIZE;i++)
	{
		temp=vector_matrix_MULTIPLY(Cube[i],gMAT);//ʸ����������,�������������뵥λ�������
		Cube_dis[i]=OrtProject(temp);//����ͶӰ
		Cube_dis[i].x+=OLED_X_MAX;
		Cube_dis[i].y+=OLED_Y_MAX;	//�������������Ļ����������⡣ȥ����˳ʱ��ת��������߽����Ҳ����������޻��ߣ�
						//������Ļ�Ŀ�Ⱦͽ���ˣ�����˵���飬����Դ�Ϊ240���߶�Ϊ432����Ȼ����Ϊ400������
						//	��Ҫע��ͼ��Ҫ�󵽳���������											
	}
	for(i=0;i<3;i++)
	{
		temp=vector_matrix_MULTIPLY(Triangle[i],gMAT);//ʸ����������
		Triangle_dis[i]=OrtProject(temp);//����ͶӰ
		Cube_dis[i].x+=OLED_X_MAX;
		Cube_dis[i].y+=OLED_Y_MAX;//�������������Ļ����������⡣ȥ����˳ʱ��ת��������߽����Ҳ����������޻��ߣ�
											//������Ļ�Ŀ�Ⱦͽ���ˣ�����˵���飬����Դ�Ϊ240���߶�Ϊ432����Ȼ����Ϊ400������
											//	��Ҫע��ͼ��Ҫ�󵽳���������
		
	}
	
	 GUI_DrawLine(Cube_dis[0].x,Cube_dis[0].y,Cube_dis[1].x,Cube_dis[1].y);
	 GUI_DrawLine(Cube_dis[1].x,Cube_dis[1].y,Cube_dis[2].x,Cube_dis[2].y);
	 GUI_DrawLine(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[0].x,Cube_dis[0].y);
	 GUI_DrawLine(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[2].x,Cube_dis[2].y);
	
	
	 GUI_DrawLine(Cube_dis[0+4].x,Cube_dis[0+4].y,Cube_dis[1+4].x,Cube_dis[1+4].y);
	 GUI_DrawLine(Cube_dis[1+4].x,Cube_dis[1+4].y,Cube_dis[2+4].x,Cube_dis[2+4].y);
	 GUI_DrawLine(Cube_dis[3+4].x,Cube_dis[3+4].y,Cube_dis[0+4].x,Cube_dis[0+4].y);
	 GUI_DrawLine(Cube_dis[3+4].x,Cube_dis[3+4].y,Cube_dis[2+4].x,Cube_dis[2+4].y);
	
	
	 GUI_DrawLine(Cube_dis[0].x,Cube_dis[0].y,Cube_dis[0+4].x,Cube_dis[0+4].y);
	 GUI_DrawLine(Cube_dis[1].x,Cube_dis[1].y,Cube_dis[1+4].x,Cube_dis[1+4].y);
	 GUI_DrawLine(Cube_dis[2].x,Cube_dis[2].y,Cube_dis[2+4].x,Cube_dis[2+4].y);
	 GUI_DrawLine(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[3+4].x,Cube_dis[3+4].y);
	
	 GUI_DrawLine(Triangle_dis[0].x,Triangle_dis[0].y,Triangle_dis[1].x,Triangle_dis[1].y);
	 GUI_DrawLine(Triangle_dis[0].x,Triangle_dis[0].y,Triangle_dis[2].x,Triangle_dis[2].y);
	 GUI_DrawLine(Triangle_dis[1].x,Triangle_dis[1].y,Triangle_dis[2].x,Triangle_dis[2].y);
	 //GUI_DrawLine(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[2].x,Cube_dis[2].y,BLACK);
	
}

///**********************************************************/
///**����: Rotate_cube
///**���ܣ���ת�����壬͸��ͶӰ
///**˵����x,y,z,�ֱ�Ϊ��Ӧ���ϵ���ת�Ƕ�
//				colorΪ��ɫ
//				XO,YO Ϊԭ��

//  ֻ�ܰ���Ԥ��ķ�����ת
//					 ��ѧ��д
//**���ߣ�  ִ��ִս
///**ʱ�䣺2015-11-30
//�޸�ʱ�䣺 2017/2/5   23:00
//					���ԭ�����õ��β�
///***********************************************************/

void RateCube(float x,float y,float z,uint32_t color,uint16_t XO,uint16_t YO)
{
	
	
//int16_t  XO;
//int16_t  YO;
	float gMAT[4][4];
	uint8_t i;
	_3Dzuobiao temp;
	_2Dzuobiao Cube_dis[8];
	
	structure_3D(gMAT);          	//����Ϊ��λ����
	Translate3D(gMAT,-4,-4,-4); 	//ƽ�Ʊ任����,��Ϊ�߳���һ��ĵ���ʱ��ͼ�������Լ���ת����ԭ��������
	Scale_3D(gMAT,4,4,4);		//�����任����
	Rotate_3D(gMAT,x,y,z);		//��ת�任����
	Translate3D(gMAT,0,0,0); 	//ƽ�Ʊ任����	   x:���ھ������ĵ��λ�ã��൱������Point0.z
					//		y�����µ���λ�� ���������ʵ���޸�
//	XO=128;		//128  ����
//	YO=64+64;	//0 ʱ��ͱ���ʾ��y=0��
	
	for(i=0;i<8;i++)
{
		temp=vector_matrix_MULTIPLY(Cube[i],gMAT);	//ʸ����������
		Cube_dis[i]=	PerProject(temp,XO,YO);		//����ͶӰ
		Cube_dis[i].x+=OLED_X_MAX;
		Cube_dis[i].y+=OLED_Y_MAX;
		Cube_dis[i].x%=OLED_X_MAX;			//�������������Ļ����������⡣ȥ����˳ʱ��ת��������߽����Ҳ����������޻��ߣ�
		Cube_dis[i].y%=OLED_Y_MAX;			//������Ļ�Ŀ�Ⱦͽ���ˣ�����˵���飬����Դ�Ϊ240���߶�Ϊ432����Ȼ����Ϊ400������
					//	��Ҫע��ͼ��Ҫ�󵽳���������
}


	 GUI_DrawLine(Cube_dis[0].x,Cube_dis[0].y,Cube_dis[1].x,Cube_dis[1].y);
	 GUI_DrawLine(Cube_dis[0].x,Cube_dis[0].y,Cube_dis[2].x,Cube_dis[2].y);
	 GUI_DrawLine(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[1].x,Cube_dis[1].y);
	 GUI_DrawLine(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[2].x,Cube_dis[2].y);
	
	
	 GUI_DrawLine(Cube_dis[0+4].x,Cube_dis[0+4].y,Cube_dis[1+4].x,Cube_dis[1+4].y);
	 GUI_DrawLine(Cube_dis[0+4].x,Cube_dis[0+4].y,Cube_dis[2+4].x,Cube_dis[2+4].y);
	 GUI_DrawLine(Cube_dis[3+4].x,Cube_dis[3+4].y,Cube_dis[1+4].x,Cube_dis[1+4].y);
	 GUI_DrawLine(Cube_dis[3+4].x,Cube_dis[3+4].y,Cube_dis[2+4].x,Cube_dis[2+4].y);
	
	
	 GUI_DrawLine(Cube_dis[0].x,Cube_dis[0].y,Cube_dis[0+4].x,Cube_dis[0+4].y);
	 GUI_DrawLine(Cube_dis[1].x,Cube_dis[1].y,Cube_dis[1+4].x,Cube_dis[1+4].y);
	 GUI_DrawLine(Cube_dis[2].x,Cube_dis[2].y,Cube_dis[2+4].x,Cube_dis[2+4].y);
	 GUI_DrawLine(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[3+4].x,Cube_dis[3+4].y);
		
}


///**********************************************************/
///**����: Rotate_cube_all
///**���ܣ�������ת�����壬͸��ͶӰ��
///**˵����x,y,z,�ֱ�Ϊ��Ӧ���ϵ���ת�Ƕ�
//			mx,my,mz Ϊƽ�Ƶ�λ
//			bx,by,bz Ϊ��Ӧ�ߵı任����
//			XO,YO Ϊԭ��
//			colorΪ��ɫ

//  ֻ�ܰ���Ԥ��ķ�����ת
//					 ��ѧ��д
//**���ߣ�  ִ��ִս
///**ʱ�䣺2015-11-30
//�޸�ʱ�䣺 2017/2/5   23:00
//					���ԭ�����õ��β�
///***********************************************************/
void RateCube_all(float x,float y,float z,float mx,float my,float mz,float bx,float by,float bz,
											int16_t XO,int16_t YO,uint32_t color)
{

	float gMAT[4][4];
	uint8_t i;
	_3Dzuobiao temp;
	_2Dzuobiao Cube_dis[8];
	
	structure_3D(gMAT);         	//����Ϊ��λ����
	Translate3D(gMAT,mx,my,mz); 	//ƽ�Ʊ任����
	Scale_3D(gMAT,bx,by,bz);	//�����任����
	Rotate_3D(gMAT,x,y,z);		//��ת�任����
	Translate3D(gMAT,0,0,32);	//ƽ�Ʊ任����	   x:���ھ������ĵ��λ�ã��൱������Point0.z
					//		   y�����µ���λ�� ���������ʵ���޸�
	for(i=0;i<8;i++)
{
		temp=vector_matrix_MULTIPLY(Cube[i],gMAT);//ʸ����������
		Cube_dis[i]=	PerProject(temp,XO,YO);   //����ͶӰ
		Cube_dis[i].x+=OLED_X_MAX;
		Cube_dis[i].y+=OLED_Y_MAX;	//�������������Ļ����������⡣ȥ����˳ʱ��ת��������߽����Ҳ����������޻��ߣ�
		Cube_dis[i].x%=OLED_X_MAX;		//������Ļ�Ŀ�Ⱦͽ���ˣ�����˵���飬����Դ�Ϊ240���߶�Ϊ432����Ȼ����Ϊ400������
		Cube_dis[i].y%=OLED_X_MAX;		//	��Ҫע��ͼ��Ҫ�󵽳���������
}


   GUI_DrawLine(Cube_dis[0].x,Cube_dis[0].y,Cube_dis[1].x,Cube_dis[1].y);
	 GUI_DrawLine(Cube_dis[0].x,Cube_dis[0].y,Cube_dis[2].x,Cube_dis[2].y);
	 GUI_DrawLine(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[1].x,Cube_dis[1].y);
	 GUI_DrawLine(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[2].x,Cube_dis[2].y);
	
	
	 GUI_DrawLine(Cube_dis[0+4].x,Cube_dis[0+4].y,Cube_dis[1+4].x,Cube_dis[1+4].y);
	 GUI_DrawLine(Cube_dis[0+4].x,Cube_dis[0+4].y,Cube_dis[2+4].x,Cube_dis[2+4].y);
	 GUI_DrawLine(Cube_dis[3+4].x,Cube_dis[3+4].y,Cube_dis[1+4].x,Cube_dis[1+4].y);
	 GUI_DrawLine(Cube_dis[3+4].x,Cube_dis[3+4].y,Cube_dis[2+4].x,Cube_dis[2+4].y);
	
	
	 GUI_DrawLine(Cube_dis[0].x,Cube_dis[0].y,Cube_dis[0+4].x,Cube_dis[0+4].y);
	 GUI_DrawLine(Cube_dis[1].x,Cube_dis[1].y,Cube_dis[1+4].x,Cube_dis[1+4].y);
	 GUI_DrawLine(Cube_dis[2].x,Cube_dis[2].y,Cube_dis[2+4].x,Cube_dis[2+4].y);
	 GUI_DrawLine(Cube_dis[3].x,Cube_dis[3].y,Cube_dis[3+4].x,Cube_dis[3+4].y);	

}


///**********************************************************/
///**����: RotatePic32x32
///**���ܣ�����ά�ռ�����תһ��32x32���ַ���ͼ��
///**˵����1�������趨�ķ�ʽ�任ÿ��ͼƬ��ÿ��������꣬����ʾ
//			2: ��ת�Ƕ�  0~360��
//			3��azȡ��ֵΪ˳ʱ����ת
//					 ��ѧ��д		
//**���ߣ�  ִ��ִս
///**ʱ�䣺2015-11-30
//�޸�ʱ�䣺 2017/2/5   23:00
//					���ԭ�����õ��β�
///***********************************************************/


void RotatePic32X32(unsigned char *dp,float ax,float ay,float az,uint32_t color,uint16_t XO,uint16_t YO)
{
//	int16_t  XO;
//	int16_t  YO;
	uint8_t i,j,k;
	uint16_t temp;
	float gMAT[4][4];
	_3Dzuobiao Point0;
	_3Dzuobiao Point1;
	_2Dzuobiao PointDis;
	
	structure_3D(gMAT);						//������λ����
	Translate3D(gMAT,-16,-16,0); 	//ƽ�Ʊ任����
	Scale_3D(gMAT,2,2,2);		 //�����任����
	Rotate_3D(gMAT,ax,ay,az);	//��ת�任����
	Translate3D(gMAT,0,0,32); 	//ƽ�Ʊ任����	   x:���ھ������ĵ��λ�ã��൱������Point0.z
					//		  y�����µ���λ�� ���������ʵ���޸�
//	XO=128;
//	YO=64;
	
	for(i=0;i<4;i++)
	{
		for(k=0;k<8;k++)
		{
			temp=0x01<<k;//_crol_(0x01,k);
			for(j=0;j<32;j++)
			{
				if(*(dp+j)&temp)
				{
					Point0.x=j;
					Point0.y=(i*8)+k;
					Point0.z=-26;		//�˲����ܹ��ı��ַ�������ת�����ĵľ���
					
					Point1=vector_matrix_MULTIPLY(Point0,gMAT);//ʸ����������
					PointDis=PerProject(Point1,XO,YO);	   //ӳ��ͶӰ
					 PointDis.x+=OLED_X_MAX;
					PointDis.y+=OLED_Y_MAX; //�������������Ļ����������⡣ȥ����˳ʱ��ת��������߽����Ҳ����������޻��ߣ�
					PointDis.x%=OLED_X_MAX;	//������Ļ�Ŀ�Ⱦͽ���ˣ�����˵���飬����Դ�Ϊ240���߶�Ϊ432����Ȼ����Ϊ400������
					PointDis.y%=OLED_Y_MAX;				//	��Ҫע��ͼ��Ҫ�󵽳���������
					GUI_DrawPoint(PointDis.x,PointDis.y,color);
				}
			}
		}
		dp+=32;
	}
}
///**********************************************************/
///**����: RotatePic29x32
///**���ܣ�����ά�ռ�����תһ��29x32���ַ���ͼ��,����ȡģ��ֻ����������С�����棬
//**			�����е�����ѡ��Ϊ����ȡģ���ֽڵ��򣬱������κ�ʱ�򶼼���
///**˵����1�������趨�ķ�ʽ�任ÿ��ͼƬ��ÿ��������꣬����ʾ
//			2: ��ת�Ƕ�  0~360��
//			3��azȡ��ֵΪ˳ʱ����ת
//					 ��ѧ��д		
//**���ߣ�  ִ��ִս
///**ʱ�䣺2015-11-30
//�޸�ʱ�䣺 2017/5/31   1200
//					���ԭ�����õ��β�
///***********************************************************/

void RotatePic29X32(unsigned char *dp,float ax,float ay,float az,uint32_t color,uint16_t XO,uint16_t YO)
{//ȡģ��ʽΪ���壬С�������棬��Ӧ����Ϊ29X32����ÿ��ȡ29���ֽڣ������У�
//	int16_t  XO;
//	int16_t  YO;
	uint8_t i,j,k;
	uint16_t temp;
	float gMAT[4][4];
	_3Dzuobiao Point0;
	_3Dzuobiao Point1;
	_2Dzuobiao PointDis;
	
	structure_3D(gMAT);		//������λ����
	Translate3D(gMAT,-16,-16,-0); 	//ƽ�Ʊ任����
	Scale_3D(gMAT,2,2,2);		//�����任����
	Rotate_3D(gMAT,ax,ay,az);	//��ת�任����
	Translate3D(gMAT,0,0,32); 	//ƽ�Ʊ任����	   x:���ھ������ĵ��λ�ã��൱������Point0.z
					//		y�����µ���λ�� ���������ʵ���޸�
//	XO=128;
//	YO=64;
	
	for(i=0;i<4;i++)			//ȡ�ĸ��ֽ���
	{
		for(k=0;k<8;k++)		//ÿ���ֽ�8λ
		{
			temp=0x01<<k;//_crol_(0x01,k);
			for(j=0;j<29;j++)
			{
				if(*(dp+j)&temp)
				{
					Point0.x=j;
					Point0.y=(i*8)+k;
					Point0.z=-26;		//�˲����ܹ��ı��ַ�������ת�����ĵľ���
					
					Point1=vector_matrix_MULTIPLY(Point0,gMAT);	//ʸ����������
					PointDis=PerProject(Point1,XO,YO);		//ӳ��ͶӰ
					 PointDis.x+=OLED_X_MAX;

					PointDis.y+=OLED_Y_MAX;//�������������Ļ����������⡣ȥ����˳ʱ��ת��������߽����Ҳ����������޻��ߣ�
					PointDis.x%=OLED_X_MAX;	//������Ļ�Ŀ�Ⱦͽ���ˣ�����˵���飬����Դ�Ϊ240���߶�Ϊ432����Ȼ����Ϊ400������
					PointDis.y%=OLED_Y_MAX;	//	��Ҫע��ͼ��Ҫ�󵽳���������
					GUI_DrawPoint(PointDis.x,PointDis.y,color);
				}
			}
		}
		dp+=29;						//ÿ��29���ֽ�
	}
}


///**********************************************************/
///**����: Rotatecircle
///**���ܣ�����ά�ռ�����תһ��Բ��
///**˵����1�������趨�ķ�ʽ�任ÿ��ͼƬ��ÿ��������꣬����ʾ
//				 2: ��ת�Ƕ�  0~360��
//				 3��azȡ��ֵΪ˳ʱ����ת
//					 ��ѧ��д		
//**���ߣ�  ִ��ִս
///**ʱ�䣺2015-11-30
//�޸�ʱ�䣺 2017/2/5   23:00
//					���ԭ�����õ��β�
///***********************************************************/

void Rotatecircle(float ax,float ay,float az,uint16_t r,uint32_t color,uint16_t XO,uint16_t YO)
{   
//	int16_t  XO;
//	int16_t  YO;
	uint8_t i;
	//uint16_t temp;
	float gMAT[4][4];
	_3Dzuobiao Point0;
	_3Dzuobiao Point3;
	
	_3Dzuobiao Point1;
	_2Dzuobiao PointDis;
	
	structure_3D(gMAT);							//���쵥λ����
	Translate3D(gMAT,-r/2,-r/2,-r/2); 	//ƽ�Ʊ任����
	//Scale_3D(gMAT,1,1,1);				 	//�����任����
	Rotate_3D(gMAT,ax,ay,az);				//��ת�任����
	Translate3D(gMAT,0,0,0);			//ƽ�Ʊ任����	
//	XO=120;													//��������
//	YO=150 ;
	
	
	
	
  
        for(i=0;i<	r+r+1;i++)
        {
					
					
					Point0.x=i;
					Point0.y=r-sqrt(r*r-(r-i)*(r-i));
					Point0.z=0;
					Point3.x=i;
					Point3.y=r+sqrt(r*r-(r-i)*(r-i));
					Point3.z=0;
					
					Point1=vector_matrix_MULTIPLY(Point0,gMAT);	//ʸ����������
					//	Translate3D(gMAT,30,30,60); //ƽ�Ʊ任����	
					
					PointDis=PerProject(Point1,XO,YO);					//ӳ��ͶӰ
					 //PointDis=OrtProject(Point1);
					PointDis.x+=OLED_X_MAX;
					PointDis.y+=OLED_Y_MAX;//�������������Ļ����������⡣ȥ����˳ʱ��ת��������߽����Ҳ����������޻��ߣ�
											//������Ļ�Ŀ�Ⱦͽ���ˣ�����˵���飬����Դ�Ϊ240���߶�Ϊ432����Ȼ����Ϊ400������
											//	��Ҫע��ͼ��Ҫ�󵽳���������
					GUI_DrawPoint(PointDis.x,PointDis.y,color);
					
					Point1=vector_matrix_MULTIPLY(Point3,gMAT);	//ʸ����������
						//Translate3D(gMAT,30,30,60); //ƽ�Ʊ任����	
					PointDis=PerProject(Point1,XO,YO);					//ӳ��ͶӰ
					 //PointDis=OrtProject(Point3);
					PointDis.x+=OLED_X_MAX;
					PointDis.y+=OLED_Y_MAX;//�������������Ļ����������⡣ȥ����˳ʱ��ת��������߽����Ҳ����������޻��ߣ�
					PointDis.x%=OLED_X_MAX;			//������Ļ�Ŀ�Ⱦͽ���ˣ�����˵���飬����Դ�Ϊ240���߶�Ϊ432����Ȼ����Ϊ400������
					PointDis.y%=OLED_Y_MAX;			//	��Ҫע��ͼ��Ҫ�󵽳���������
					GUI_DrawPoint(PointDis.x,PointDis.y,color);
                         
        }
	
	
		
	
	
	
	
}