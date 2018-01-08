/**
* @par 			Copyright (C): Personal CoderDMBai
* @file         ZhiZhangCar.ino
* @author       CoderDMBai
* @version      V1.0.0
* @date         2017.12.13
* @brief        智障小车
* @details
* @par History
*				#功能介绍：
					1.自动避障，不出车祸
				#传感器清单
				    1、超声波传感器 * 1
				    2、红外线避障传感器 * 4
				    3、1602显示屏 * 1
				    4、蓝牙模块 * 1
*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(A3, A4, A5, 13, 12, 7, 8);

/* - - - - - - - - - - - - - - - - - -模板宏定义 - - - - - - - - - - - - - - - - - -*/
#define _VERSION                      "v1.0.0"                  //版本号
#define _DEVICE                       "ZhiZhangCar"             //设备名称
#define _DATE                         "2017-12-13"              //烧录日期

/* - - - - - - - - - - - - - - - - - - 变量声明 - - - - - - - - - - - - - - - - - - -*/
// 电机模块
int Left_motor_go = 6;      // 左电机前进
int Left_motor_back = 9;    // 左电机后退
int Right_motor_go = 11;    // 右电机前进
int Right_motor_back = 10;  // 右电机后退

// 超声波模块
int Trig = A0;              // Trig 触发脚(P2.1)
int Echo = A1;              // Echo 回声脚(P2.0)

// 红外避障传感器
int IrEludeLeft = 2;        // 左边红外避障传感器 3
int IrEludeLeftFront = 3;  // 左前红外避障传感器 2
int IrEludeRightFront = 4;  // 右前红外避障传感器  4
int IrEludeRight = 5;       // 右边红外避障传感器  5

// 红外避障传感器状态
int SR;                     // 左边
int SL;                     // 右边
int SRF;                    // 左前
int SLF;                    // 右前

// 测速传感器

// 记录前方障碍物距离
int Front_Distance = 0;

void setup() {
  // 设置串口波特率
  Serial.begin(9600);       

  //初始化电机驱动IO为输出方式
  pinMode(Left_motor_go, OUTPUT); 
  pinMode(Left_motor_back, OUTPUT); 
  pinMode(Right_motor_go, OUTPUT);
  pinMode(Right_motor_back, OUTPUT);

  // 初始化超声波引脚
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);

  // 初始化红外避障传感器
  pinMode(IrEludeLeft, INPUT); 
  pinMode(IrEludeLeftFront, INPUT); 
  pinMode(IrEludeRightFront, INPUT); 
  pinMode(IrEludeRight, INPUT);

  lcd.begin(16,2);
  pinMode(A2, OUTPUT);
  Control_display(' ');
}

/* - - - - - - - - - - - - - - - - - - - -↓ 智能小车的基本动作 ↓- - - -   - - - - - - - - - - - - - */
/**
   前进
*/
void run()
{
  digitalWrite(Left_motor_go, HIGH);
  digitalWrite(Left_motor_back, LOW);
  analogWrite(Left_motor_go, 80);
  analogWrite(Left_motor_back, 0);
  digitalWrite(Right_motor_go, HIGH);
  digitalWrite(Right_motor_back, LOW);     
  analogWrite(Right_motor_go, 80);
  analogWrite(Right_motor_back, 0);
}

/**
   左转(左轮不动，右轮前进)
*/
void left()
{
  digitalWrite(Left_motor_go, LOW);  
  digitalWrite(Left_motor_back, LOW);
  analogWrite(Left_motor_go, 0); 
  analogWrite(Left_motor_back, 0); 
  digitalWrite(Right_motor_go, HIGH);
  digitalWrite(Right_motor_back, LOW);     
  analogWrite(Right_motor_go, 80);
  analogWrite(Right_motor_back, 0);
//  delay(time * 100);               
}

/**
   左转(左轮后退，右轮前进)
*/
void spin_left(int time)
{
  digitalWrite(Left_motor_go, LOW);  
  digitalWrite(Left_motor_back, HIGH);
  analogWrite(Left_motor_go, 0); 
  analogWrite(Left_motor_back, 80); 
  digitalWrite(Right_motor_go, HIGH);
  digitalWrite(Right_motor_back, LOW);     
  analogWrite(Right_motor_go, 80);
  analogWrite(Right_motor_back, 0);
  delay(time * 100);                
}

/**
   右转(右轮不动，左轮前进)
*/
void right()
{
  digitalWrite(Left_motor_go, HIGH);  
  digitalWrite(Left_motor_back, LOW);
  analogWrite(Left_motor_go, 80); 
  analogWrite(Left_motor_back, 0);
  digitalWrite(Right_motor_go, LOW);
  digitalWrite(Right_motor_back, LOW);
  analogWrite(Right_motor_go, 0); 
  analogWrite(Right_motor_back, 0);
//  delay(time * 100);                
}

/**
   右转(右轮后退，左轮前进)
*/
void spin_right(int time)
{
  digitalWrite(Left_motor_go, HIGH);    
  digitalWrite(Left_motor_back, LOW);
  analogWrite(Left_motor_go, 80); 
  analogWrite(Left_motor_back, 0); 
  digitalWrite(Right_motor_go, LOW);   
  digitalWrite(Right_motor_back, HIGH);
  analogWrite(Right_motor_go, 0); 
  analogWrite(Right_motor_back, 80);
  delay(time * 100);                 
}

/**
   后退
*/
void back()
{
  digitalWrite(Left_motor_go, LOW);   
  digitalWrite(Left_motor_back, HIGH);
  analogWrite(Left_motor_go, 0);
  analogWrite(Left_motor_back, 80);  
  digitalWrite(Right_motor_go, LOW);   
  digitalWrite(Right_motor_back, HIGH);
  analogWrite(Right_motor_go, 0);
  analogWrite(Right_motor_back, 80);
//  delay(time * 100);                 
}

/**
   刹车，停车
*/
void brake()
{
  digitalWrite(Right_motor_go, LOW);
  digitalWrite(Right_motor_back, LOW);
  digitalWrite(Left_motor_go, LOW);
  digitalWrite(Left_motor_back, LOW);
//  delay(time * 100);        
}
/* - - - - - - - - - - - - - - - - - - - -↑ 智能小车的基本动作 ↑- - - - - - - - - - - - - - - - - - */
/**
  量出前方距离
 */
void Distance()
{
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW); 
  float Fdistance = pulseIn(Echo, HIGH);  // 读取高电平时间(单位：微秒)
  Fdistance= Fdistance/58;       //为什么除以58等于厘米，  Y米=（X秒*344）/2
  // X秒=（ 2*Y米）/344 ==》X秒=0.0058*Y米 ==》厘米=微秒/58
//  Serial.print("Distance:");      //输出距离（单位：厘米）
//  Serial.println(Fdistance);         //显示距离
  Front_Distance =  Fdistance;
  Distance_display(Fdistance);
}

/**
 */
void Distance_display(int Distance)//显示距离
{
  if((2<Distance)&(Distance<400))
  {
    lcd.home();        //把光标移回左上角，即从头开始输出   
    lcd.print("   KoalaRobot");       //显示
    lcd.setCursor(1,2);   //把光标定位在第2行，第6列
    lcd.print("Distance:");
    lcd.print(Distance);       //显示距离
    lcd.print("cm");          //显示
  }
  else
  {
    lcd.home();        //把光标移回左上角，即从头开始输出  
    lcd.print("   Out of range!!! ");       //显示
  }
  delay(250);
  lcd.clear();
}

/**
 */
void Control_display(char c)
{
  lcd.home();        //把光标移回左上角，即从头开始输出   
  lcd.print("   KoalaRobot");       //显示
  lcd.setCursor(1,2);   //把光标定位在第2行，第6列
  if(c == 'R')
  {
    lcd.print("  Turn Right");
  }
  else if(c == 'U')
  {
    lcd.print("  Go Forward");
  }
  else if(c == 'D')
  {
    lcd.print("   Back Up");
  }
  else if(c == 'S')
  {
    lcd.print("   Stop Car");
  }
  else if(c == 'L')
  {
    lcd.print("   Turn Left");
  }
  else
  {
    lcd.print("Mode Selection");
  }
}

void loop() {
  while(Serial.available())
  {
    char c = Serial.read();
    Serial.println(c);
    if(c == 'A')
    {
      while( 1 )
      {
        if(Serial.available())
        {
          char ch = Serial.read();
          if(ch == 'S')
          {
            brake();
            break;
          }
        }
        
        Distance();

        SL = digitalRead(IrEludeLeft); 
        SR = digitalRead(IrEludeRight); 
        SLF = digitalRead(IrEludeLeftFront);
        SRF = digitalRead(IrEludeRightFront);
    
        // 前方15厘米处有障碍物
        if(Front_Distance < 15)
        {
          spin_right(3);
        }
        // 左前或左边有障碍物
        else if(SLF == LOW || SL == LOW)
        {
          spin_right(3);
        }
        // 右前或右边有障碍物
        else if(SRF == LOW || SR == LOW)
        {
          spin_left(3);
        }
        // 左前和左都有障碍物
        else if(SLF == LOW && SL == LOW)
        {
          spin_right(3);
        }
        // 右前和右边都有障碍物
        else if(SRF == LOW && SR == LOW)
        {
          spin_left(3);
        }
        // 左前和右前都有障碍物
        else if(SLF == LOW && SRF == LOW)
        {
          spin_right(6);
        }
        // 前面半周都有障碍物，原地旋转一周
        else if(SL == LOW && SLF == LOW && SR == LOW && SRF == LOW)
        {
          spin_right(6);
        }
        else
        {
          run();
        }
      }
    }
    else if(c == 'L')
    {
      Control_display('L');
      left();
    }
    else if(c == 'R')
    {
      Control_display('R');
      right();
    }
    else if(c == 'U')
    {
      Control_display('U');
      run();
    }
    else if(c == 'D')
    {
      Control_display('D');
      back();
    }
    else if(c == 'S')
    {
      Control_display('S');
       brake();
    }
    else
    {
      Control_display(' ');
    }
  }
}
