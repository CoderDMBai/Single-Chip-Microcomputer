#ifndef __BSTCAR_H__
#define __BSTCAR_H__

/************����С��ͷ�ļ�*************/
// ����С������ģ������IO�� 
sbit IN1 = P1^1;	// �ߵ�ƽ1 ����(��ת)����
sbit IN2 = P1^2;	// �ߵ�ƽ1 ǰ��(��ת)����
sbit IN3 = P1^3;	// �ߵ�ƽ1 ǰ��(��ת)�ҵ��
sbit IN4 = P1^4;	// �ߵ�ƽ1 ����(��ת)�ҵ��
sbit EN1 = P1^0; 	// �ߵ�ƽʹ�� 
sbit EN2 = P1^5; 	// �ߵ�ƽʹ��  
// sbit Left_motor_pwm = P1^0; 	// �ߵ�ƽʹ�� 
// sbit Right_motor_pwm = P1^5; 	// �ߵ�ƽʹ��  

// ���峬����Echo��Trig
sbit RX = P0^1;	// Echo
sbit TX = P0^0; // Trig

// ��������߱��ϴ�����
sbit IrEludeLeft = P0^5;        // ��ߺ�����ϴ����� 
sbit IrEludeLeftFront = P0^4;   // ��ǰ������ϴ����� 
sbit IrEludeRightFront = P0^3;  // ��ǰ������ϴ����� 
sbit IrEludeRight = P0^2;       // �ұߺ�����ϴ����� 

#define Left_moto_go      {EN1=1,IN1=1,IN2=0;}   //������ǰ��
#define Left_moto_back    {EN1=1,IN1=0,IN2=1;}   //��ߵ�������
#define Left_moto_Stop    {EN1=0;}         		 //��ߵ��ֹͣ                     
#define Right_moto_go     {EN2=1,IN3=0,IN4=1;}   //�ұߵ����ǰ��
#define Right_moto_back   {EN2=1,IN3=1,IN4=0;}   //�ұߵ�������
#define Right_moto_Stop   {EN2=0;}	       		 //�ұߵ��ֹͣ  

// #define Left_moto_go      {IN1=1,IN2=0;}   //������ǰ��
// #define Left_moto_back    {IN1=0,IN2=1;}   //��ߵ�������
// #define Left_moto_Stop    {Left_motor_pwm=0;}         		 //��ߵ��ֹͣ                     
// #define Right_moto_go     {IN3=0,IN4=1;}   //�ұߵ����ǰ��
// #define Right_moto_back   {IN3=1,IN4=0;}   //�ұߵ�������
// #define Right_moto_Stop   {Right_motor_pwm=0;}	       		 //�ұߵ��ֹͣ 

#endif