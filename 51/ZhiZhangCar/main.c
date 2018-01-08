/**
* @par 			Copyright (C): Personal CoderDMBai
* @file         main.c
* @author       CoderDMBai
* @version      V1.0.0
* @date         2017.12.20
* @brief        智障小车
* @details
* @par History
*				#功能介绍：
					1.自动避障，不出车祸
				#传感器清单
				    1、超声波传感器 * 1
				    2、红外线避障传感器 * 4
*/

#include <reg52.h>			// 包含52单片机系统头文件
#include <STDIO.H>			// 包含 printf()
#include "bst_car.h"	 	// 包含bst_car.h智障小车头文件
//#include <AT89X51.H>		// 包含对 TH0、TL0、TR0、ET0、TMOD、SCON、TH1、TL1、TR1、TI 的定义
#include <intrins.h>		// 包含对 _nop_() 的定义

/**
	宏定义
*/
#define uchar unsigned char
#define uint unsigned int

/**
	变量声明
*/
bit flag = 0;				 // 中断溢出标志
uint time = 0;				 // 记录时间间隔
float Front_Distance = 0;	 // 记录前方障碍物距离

// uchar pwm_val_left  = 0; 	 //左轮PWM值
// uchar pwm_val_right = 0; 	 //右轮PWM值

// //速度调节变量 0-20,0最小,20最大
// unsigned char push_val_left = 5;  //左电机占空比 push_val_left/20 
// unsigned char push_val_right = 5; //右电机占空比 push_val_right/20 

// bit Right_PWM_ON = 1;	      //右电机PWM开关
// bit Left_PWM_ON = 1;		  //左电机PWM开关

/* - - - - - - - - - - - - - - - - - - - -↓      公共方法      ↓- - - -   - - - - - - - - - - - - - */
/**
	串口初始化函数
*/
void Initial_Com(void)
{
	/// 超声波单独工作
	// TMOD = 0x21;              // 定时器T1，在方式1中断产生波特率，设T0为方式1，GATE=1；
    // TH1 = 0xFD;				  // 波特率设置为9600
    // TL1 = 0xFD;
	// TR1 = 1;                  // 开启定时器
	// TH0 = 0;  			  	  // 1ms定时
	// TL0 = 0;
    // TR0 = 1;
	// ET0 = 1;				  // 允许T0中断
    // TI = 1;
    // EA = 1;                   // 开启总中断

    /// 超声波 + 红外线
    TMOD = 0x21;              // 定时器T1，在方式1中断产生波特率，设T0为方式1，GATE=1；
    TH1 = 0xFD;				  // 波特率设置为9600
    TL1 = 0xFD;
	TR1 = 1;                  // 开启定时器
	TH0 = 0;  			  	  // 1ms定时
	TL0 = 0;
    TR0 = 1;
	ET0 = 1;				  // 允许T0中断
    TI = 1;
    EA = 1;                   // 开启总中断

    /// 超声波 + 红外线 + 电机调速

	//----------------------------------------------------------------------
	
    // 红外线 + 调速     timer0 是 pwm
    // P2 = 0XC0;    //关电机	
	// TMOD = 0X01;  //定时器工作方式1
    // TH0 = 0XFC;   //1ms定时，装入初值
    // TL0 = 0X66;
    // TR0 = 1;		//启动T0工作
    // ET0 = 1;		//允许T0中断																		  -
    // EA = 1;	    //开总中断 
    
    // 超声波 + 调速     timer0是 pwm     timer1是 超声波
	
    

    /// 超声波单独工作
	// TMOD = 0x21;              // 定时器T1，在方式1中断产生波特率，设T0为方式1，GATE=1；
    // TH1 = 0xFD;				  // 波特率设置为9600
    // TL1 = 0xFD;
	// TR1 = 1;                  // 开启定时器
	// TH0 = 0;  			  	  // 1ms定时
	// TL0 = 0;
    // TR0 = 1;
	// ET0 = 1;				  // 允许T0中断
    // TI = 1;
    // EA = 1;                   //开启总中断
}

/**
	延时函数
*/
void delay(uint xms)				
{
    uint i,j;
	for(i=xms;i>0;i--)		      // i=xms即延时约xms毫秒
    for(j=112;j>0;j--);
}
/* - - - - - - - - - - - - - - - - - - - -↑      公共方法      ↑- - - -   - - - - - - - - - - - - - */

/* - - - - - - - - - - - - - - - - - - - -↓ 智能小车的基本动作 ↓- - - -   - - - - - - - - - - - - - */
/**
	前进
*/
void run(void)
{
	Left_moto_go;
	// push_val_left = 5;		  //更新指定管脚的PWM值，更改可实现控速（0-20）
	Right_moto_go; 
	// push_val_right = 5;	  //更新指定管脚的PWM值，更改可实现控速（0-20）
}

/**
   左转(左轮不动，右轮前进)
*/
void left(void)
{
	Left_moto_Stop;
	Right_moto_go;
	// push_val_right = 5;	  //更新指定管脚的PWM值，更改可实现控速（0-20）
}

/**
   左转(左轮后退，右轮前进)
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
   右转(右轮不动，左轮前进)
*/
void right(void)
{
	Left_moto_go;
	// push_val_left = 5;		  //更新指定管脚的PWM值，更改可实现控速（0-20）
	Right_moto_back;
}

/**
   右转(右轮后退，左轮前进)
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
   后退
*/
void back(void)
{
	Left_moto_back;
	Right_moto_back;
}

/**
   刹车，停车
*/
void brake(void)
{
	Left_moto_Stop;
	Right_moto_Stop;
}

/**
	左电机调速,调节 push_val_left 的值改变电机转速,占空比
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
//           if(pwm_val_left >= 20) // 这里的20代表的是pwm为20ms即50hz
// 	      pwm_val_left = 0;
//      }
//      else    
//      {
//           Left_motor_pwm = 0; // 若未开启PWM则PWMA=0 左电机停止
//      }
// }
/**
	右电机调速	,调节 pwm_val_right 的值改变电机转速,占空比
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
// 	    if(pwm_val_right >= 20) // 这里的20代表的是pwm为20ms即50hz
// 	    pwm_val_right = 0;
//     }
// 	else    
//     {
//         Right_motor_pwm = 0;  // 若未开启PWM则PWMB=0右电机停止
// 	}
// }

/**
	TIMER0中断服务子函数产生PWM信号，用于电机的控速
*/
// void timer0()interrupt 1
// {
//      TH0=0XFC;	      		  // 1Ms定时
// 	 TL0=0X66;
// 	 pwm_val_left ++;
// 	 pwm_val_right ++;
// 	 pwm_out_left_motor();
// 	 pwm_out_right_motor();
// }
/* - - - - - - - - - - - - - - - - - - - -↑ 智能小车的基本动作 ↑- - - - - - - - - - - - - - - - - - */

/* - - - - - - - - - - - - - - - - - - - -↓   超声波功能实现   ↓- - - - - - - - - - - - - - - - - - */
/**
	计算障碍物距离CM
*/
void Distance(void)
{
    time = TH0 * 256 + TL0;
    TH0 = 0;
    TL0 = 0;
    Front_Distance = (time * 1.87) / 100;     	// 算出来是CM
    if((Front_Distance >= 7000) || flag == 1)   // 超出测量
    {
        flag = 0;
        printf("-----\n"); 
    }    
    printf("S=%d\n",(uint)Front_Distance); 
}

/**
	TIMER1中断用来计数器溢出,超过测距范围
*/
void zd0() interrupt 1
{
    flag = 1;
}

/**
	T1中断用来扫描数码管和计800MS启动模块
*/
void StartModule(void)
{
    TX = 1;                     // 800MS  启动一次模块
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

/* - - - - - - - - - - - - - - - - - - - -↑   超声波功能实现   ↑- - - - - - - - - - - - - - - - - - */
/**
	主函数
*/
void main(void)
{
    Initial_Com();
	run();
	while(1)				  // 无限循环
	{
		StartModule();
        while(!RX);           // 当RX为零时等待
        TR0 = 1;              // 开启计数
        while(RX);            // 当RX为1计数并等待
        TR0 = 0;              // 关闭计数
        Distance();           // 计算
		delay(10);
		
		// 前方15厘米处有障碍物
		if(Front_Distance < 15)
		{
			spin_right(3);
		}
		// 左前或左边有障碍物
        else if(IrEludeLeftFront == 0 || IrEludeLeft == 0)
        {
          spin_right(3);
        }
        // 右前或右边有障碍物
        else if(IrEludeRightFront == 0 || IrEludeRight == 0)
        {
          spin_left(3);
        }
        // 左前和左都有障碍物
        else if(IrEludeLeftFront == 0 && IrEludeLeft == 0)
        {
          spin_right(3);
        }
        // 右前和右边都有障碍物
        else if(IrEludeRightFront == 0 && IrEludeRight == 0)
        {
          spin_left(3);
        }
        // 左前和右前都有障碍物
        else if(IrEludeLeftFront == 0 && IrEludeRightFront == 0)
        {
          spin_right(12);
        }
        // 前面半周都有障碍物，原地旋转一周
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