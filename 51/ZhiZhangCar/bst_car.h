#ifndef __BSTCAR_H__
#define __BSTCAR_H__

/************智障小车头文件*************/
// 定义小车驱动模块输入IO口 
sbit IN1 = P1^1;	// 高电平1 后退(反转)左电机
sbit IN2 = P1^2;	// 高电平1 前进(正转)左电机
sbit IN3 = P1^3;	// 高电平1 前进(正转)右电机
sbit IN4 = P1^4;	// 高电平1 后退(反转)右电机
sbit EN1 = P1^0; 	// 高电平使能 
sbit EN2 = P1^5; 	// 高电平使能  
// sbit Left_motor_pwm = P1^0; 	// 高电平使能 
// sbit Right_motor_pwm = P1^5; 	// 高电平使能  

// 定义超声波Echo与Trig
sbit RX = P0^1;	// Echo
sbit TX = P0^0; // Trig

// 定义红外线避障传感器
sbit IrEludeLeft = P0^5;        // 左边红外避障传感器 
sbit IrEludeLeftFront = P0^4;   // 左前红外避障传感器 
sbit IrEludeRightFront = P0^3;  // 右前红外避障传感器 
sbit IrEludeRight = P0^2;       // 右边红外避障传感器 

#define Left_moto_go      {EN1=1,IN1=1,IN2=0;}   //左电机向前走
#define Left_moto_back    {EN1=1,IN1=0,IN2=1;}   //左边电机向后走
#define Left_moto_Stop    {EN1=0;}         		 //左边电机停止                     
#define Right_moto_go     {EN2=1,IN3=0,IN4=1;}   //右边电机向前走
#define Right_moto_back   {EN2=1,IN3=1,IN4=0;}   //右边电机向后走
#define Right_moto_Stop   {EN2=0;}	       		 //右边电机停止  

// #define Left_moto_go      {IN1=1,IN2=0;}   //左电机向前走
// #define Left_moto_back    {IN1=0,IN2=1;}   //左边电机向后走
// #define Left_moto_Stop    {Left_motor_pwm=0;}         		 //左边电机停止                     
// #define Right_moto_go     {IN3=0,IN4=1;}   //右边电机向前走
// #define Right_moto_back   {IN3=1,IN4=0;}   //右边电机向后走
// #define Right_moto_Stop   {Right_motor_pwm=0;}	       		 //右边电机停止 

#endif