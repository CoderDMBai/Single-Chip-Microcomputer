/*
  # 代码说明
    Arduino进入蓝牙AT模式代码
    
  # 接线
    Arduino VCC   --- 5V
    Arduino GND   --- GND
    Arduino Pin10 --- TXD
    Arduino Pin11 --- RXD

  # 流程
    1.接线
    2.选择端口
    3.烧录代码
    4.打开 Arduino IDE 的串口监视器，将输出格式设置为 Both：NL & CR
    5.输入 AT，串口监视器返回 OK 
  
  # 常用 AT 指令
    AT+ORGL           # 恢复出厂模式
    AT+NAME=<Name>    # 设置蓝牙名称
    AT+ROLE=0         # 设置蓝牙为从模式
    AT+CMODE=1        # 设置蓝牙为任意设备连接模式
    AT+PSWD=<Pwd>     # 设置蓝牙匹配密码
    
  # 备注
    暂时仅适用于 HC-05
*/
#include <SoftwareSerial.h> 

// Pin10为RX，接HC-05的TXD
// Pin11为TX，接HC-05的RXD
SoftwareSerial BT(10, 11); 
char val;

void setup() {
  Serial.begin(9600); 
  Serial.println("BT is ready!");
  // HC-05默认，38400
  BT.begin(9600);
}

void loop() {
  if (Serial.available()) {
    val = Serial.read();
    BT.print(val);
  }

  if (BT.available()) {
    val = BT.read();
    Serial.print(val);
  }
}
