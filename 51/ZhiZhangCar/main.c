/**
* @par 			Copyright (C): Personal CoderDMBai
* @file         main.c
* @author       CoderDMBai
* @version      V1.0.0
* @date         2017.12.20
* @brief        ����С��
* @details
* @par History
*				#���ܽ��ܣ�
					1.�Զ����ϣ���������
				#�������嵥
				    1�������������� * 1
				    2�������߱��ϴ����� * 4
*/

#include <reg52.h>			// ����52��Ƭ��ϵͳͷ�ļ�
#include <STDIO.H>			// ���� printf()
#include "bst_car.h"	 	// ����bst_car.h����С��ͷ�ļ�
//#include <AT89X51.H>		// ������ TH0��TL0��TR0��ET0��TMOD��SCON��TH1��TL1��TR1��TI �Ķ���
#include <intrins.h>		// ������ _nop_() �Ķ���

/**
	�궨��
*/
#define uchar unsigned char
#define uint unsigned int

/**
	��������
*/
bit flag = 0;				 // �ж������־
uint time = 0;				 // ��¼ʱ����
float Front_Distance = 0;	 // ��¼ǰ���ϰ������

// uchar pwm_val_left  = 0; 	 //����PWMֵ
// uchar pwm_val_right = 0; 	 //����PWMֵ

// //�ٶȵ��ڱ��� 0-20,0��С,20���
// unsigned char push_val_left = 5;  //����ռ�ձ� push_val_left/20 
// unsigned char push_val_right = 5; //�ҵ��ռ�ձ� push_val_right/20 

// bit Right_PWM_ON = 1;	      //�ҵ��PWM����
// bit Left_PWM_ON = 1;		  //����PWM����

/* - - - - - - - - - - - - - - - - - - - -��      ��������      ��- - - -   - - - - - - - - - - - - - */
/**
	���ڳ�ʼ������
*/
void Initial_Com(void)
{
	/// ��������������
	// TMOD = 0x21;              // ��ʱ��T1���ڷ�ʽ1�жϲ��������ʣ���T0Ϊ��ʽ1��GATE=1��
    // TH1 = 0xFD;				  // ����������Ϊ9600
    // TL1 = 0xFD;
	// TR1 = 1;                  // ������ʱ��
	// TH0 = 0;  			  	  // 1ms��ʱ
	// TL0 = 0;
    // TR0 = 1;
	// ET0 = 1;				  // ����T0�ж�
    // TI = 1;
    // EA = 1;                   // �������ж�

    /// ������ + ������
    TMOD = 0x21;              // ��ʱ��T1���ڷ�ʽ1�жϲ��������ʣ���T0Ϊ��ʽ1��GATE=1��
    TH1 = 0xFD;				  // ����������Ϊ9600
    TL1 = 0xFD;
	TR1 = 1;                  // ������ʱ��
	TH0 = 0;  			  	  // 1ms��ʱ
	TL0 = 0;
    TR0 = 1;
	ET0 = 1;				  // ����T0�ж�
    TI = 1;
    EA = 1;                   // �������ж�

    /// ������ + ������ + �������

	//----------------------------------------------------------------------
	
    // ������ + ����     timer0 �� pwm
    // P2 = 0XC0;    //�ص��	
	// TMOD = 0X01;  //��ʱ��������ʽ1
    // TH0 = 0XFC;   //1ms��ʱ��װ���ֵ
    // TL0 = 0X66;
    // TR0 = 1;		//����T0����
    // ET0 = 1;		//����T0�ж�																		  -
    // EA = 1;	    //�����ж� 
    
    // ������ + ����     timer0�� pwm     timer1�� ������
	
    

    /// ��������������
	// TMOD = 0x21;              // ��ʱ��T1���ڷ�ʽ1�жϲ��������ʣ���T0Ϊ��ʽ1��GATE=1��
    // TH1 = 0xFD;				  // ����������Ϊ9600
    // TL1 = 0xFD;
	// TR1 = 1;                  // ������ʱ��
	// TH0 = 0;  			  	  // 1ms��ʱ
	// TL0 = 0;
    // TR0 = 1;
	// ET0 = 1;				  // ����T0�ж�
    // TI = 1;
    // EA = 1;                   //�������ж�
}

/**
	��ʱ����
*/
void delay(uint xms)				
{
    uint i,j;
	for(i=xms;i>0;i--)		      // i=xms����ʱԼxms����
    for(j=112;j>0;j--);
}
/* - - - - - - - - - - - - - - - - - - - -��      ��������      ��- - - -   - - - - - - - - - - - - - */

/* - - - - - - - - - - - - - - - - - - - -�� ����С���Ļ������� ��- - - -   - - - - - - - - - - - - - */
/**
	ǰ��
*/
void run(void)
{
	Left_moto_go;
	// push_val_left = 5;		  //����ָ���ܽŵ�PWMֵ�����Ŀ�ʵ�ֿ��٣�0-20��
	Right_moto_go; 
	// push_val_right = 5;	  //����ָ���ܽŵ�PWMֵ�����Ŀ�ʵ�ֿ��٣�0-20��
}

/**
   ��ת(���ֲ���������ǰ��)
*/
void left(void)
{
	Left_moto_Stop;
	Right_moto_go;
	// push_val_right = 5;	  //����ָ���ܽŵ�PWMֵ�����Ŀ�ʵ�ֿ��٣�0-20��
}

/**
   ��ת(���ֺ��ˣ�����ǰ��)
*/
void spin_left(uint time)
{
	Left_moto_back;
	// push_val_left = 5;
	Right_moto_go;
	// push_val_right = 5;
	delay(time * 100);
}


/**
   ��ת(���ֲ���������ǰ��)
*/
void right(void)
{
	Left_moto_go;
	// push_val_left = 5;		  //����ָ���ܽŵ�PWMֵ�����Ŀ�ʵ�ֿ��٣�0-20��
	Right_moto_back;
}

/**
   ��ת(���ֺ��ˣ�����ǰ��)
*/
void spin_right(uint time)
{
	Right_moto_back;
	// push_val_left = 5;
	Left_moto_go;
	// push_val_right = 5;
	delay(time * 100); 
}

/**
   ����
*/
void back(void)
{
	Left_moto_back;
	Right_moto_back;
}

/**
   ɲ����ͣ��
*/
void brake(void)
{
	Left_moto_Stop;
	Right_moto_Stop;
}

/**
	��������,���� push_val_left ��ֵ�ı���ת��,ռ�ձ�
*/
// void pwm_out_left_motor(void)
// {  
//      if(Left_PWM_ON)
//      {
//           if(pwm_val_left <= push_val_left)
// 	      {
// 	          Left_motor_pwm = 1; 
// 	      }
// 	      else 
// 	      {
// 	          Left_motor_pwm = 0;
//           }
//           if(pwm_val_left >= 20) // �����20�������pwmΪ20ms��50hz
// 	      pwm_val_left = 0;
//      }
//      else    
//      {
//           Left_motor_pwm = 0; // ��δ����PWM��PWMA=0 ����ֹͣ
//      }
// }
/**
	�ҵ������	,���� pwm_val_right ��ֵ�ı���ת��,ռ�ձ�
*/
// void pwm_out_right_motor(void)
// { 
//     if(Right_PWM_ON)
//     { 
//         if(pwm_val_right <= push_val_right)	
// 	    {
// 	        Right_motor_pwm = 1; 							
//         }
// 	    else 
// 	    {
// 	        Right_motor_pwm = 0;
//         }
// 	    if(pwm_val_right >= 20) // �����20�������pwmΪ20ms��50hz
// 	    pwm_val_right = 0;
//     }
// 	else    
//     {
//         Right_motor_pwm = 0;  // ��δ����PWM��PWMB=0�ҵ��ֹͣ
// 	}
// }

/**
	TIMER0�жϷ����Ӻ�������PWM�źţ����ڵ���Ŀ���
*/
// void timer0()interrupt 1
// {
//      TH0=0XFC;	      		  // 1Ms��ʱ
// 	 TL0=0X66;
// 	 pwm_val_left ++;
// 	 pwm_val_right ++;
// 	 pwm_out_left_motor();
// 	 pwm_out_right_motor();
// }
/* - - - - - - - - - - - - - - - - - - - -�� ����С���Ļ������� ��- - - - - - - - - - - - - - - - - - */

/* - - - - - - - - - - - - - - - - - - - -��   ����������ʵ��   ��- - - - - - - - - - - - - - - - - - */
/**
	�����ϰ������CM
*/
void Distance(void)
{
    time = TH0 * 256 + TL0;
    TH0 = 0;
    TL0 = 0;
    Front_Distance = (time * 1.87) / 100;     	// �������CM
    if((Front_Distance >= 7000) || flag == 1)   // ��������
    {
        flag = 0;
        printf("-----\n"); 
    }    
    printf("S=%d\n",(uint)Front_Distance); 
}

/**
	TIMER1�ж��������������,������෶Χ
*/
void zd0() interrupt 1
{
    flag = 1;
}

/**
	T1�ж�����ɨ������ܺͼ�800MS����ģ��
*/
void StartModule(void)
{
    TX = 1;                     // 800MS  ����һ��ģ��
    _nop_(); 
    _nop_(); 
    _nop_(); 
    _nop_(); 
    _nop_(); 
    _nop_(); 
    _nop_(); 
    _nop_(); 
    _nop_(); 
    _nop_(); 
    _nop_(); 
    _nop_(); 
    _nop_(); 
    _nop_(); 
    _nop_(); 
    _nop_(); 
    _nop_();
    _nop_(); 
    _nop_(); 
    _nop_(); 
    _nop_();
    TX = 0;
}

/* - - - - - - - - - - - - - - - - - - - -��   ����������ʵ��   ��- - - - - - - - - - - - - - - - - - */
/**
	������
*/
void main(void)
{
    Initial_Com();
	run();
	while(1)				  // ����ѭ��
	{
		StartModule();
        while(!RX);           // ��RXΪ��ʱ�ȴ�
        TR0 = 1;              // ��������
        while(RX);            // ��RXΪ1�������ȴ�
        TR0 = 0;              // �رռ���
        Distance();           // ����
		delay(10);
		
		// ǰ��15���״����ϰ���
		if(Front_Distance < 15)
		{
			spin_right(3);
		}
		// ��ǰ��������ϰ���
        else if(IrEludeLeftFront == 0 || IrEludeLeft == 0)
        {
          spin_right(3);
        }
        // ��ǰ���ұ����ϰ���
        else if(IrEludeRightFront == 0 || IrEludeRight == 0)
        {
          spin_left(3);
        }
        // ��ǰ�������ϰ���
        else if(IrEludeLeftFront == 0 && IrEludeLeft == 0)
        {
          spin_right(3);
        }
        // ��ǰ���ұ߶����ϰ���
        else if(IrEludeRightFront == 0 && IrEludeRight == 0)
        {
          spin_left(3);
        }
        // ��ǰ����ǰ�����ϰ���
        else if(IrEludeLeftFront == 0 && IrEludeRightFront == 0)
        {
          spin_right(12);
        }
        // ǰ����ܶ����ϰ��ԭ����תһ��
        else if(IrEludeLeft == 0 && IrEludeLeftFront == 0 && IrEludeRight == 0 && IrEludeRightFront == 0)
        {
          spin_right(12);
        }
        else
        {
          run();
        }
	}
}