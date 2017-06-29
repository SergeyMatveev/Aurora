
#include <IRremote.h>
int receiverpin = 11;//红外接收信号引脚
int pinI1=8;//定义I1接口
int pinI2=9;//定义I2接口
int speedpin1=10;//定义EA(PWM调速)接口
int pinI3=4;//定义I3接口
int pinI4=5;//定义I4接口
int speedpin2=6;//定义EB(PWM调速)接口

//红外遥控逻辑代码 
#define ADVAN 0x1081F   //遥控器>>键
#define BAC   0xFF      //遥控器<<键
#define STO   0x147DF   //遥控器>|键
IRrecv irrecv(receiverpin);//初始化
decode_results results;//定义结构体类型

void setup()
{
  pinMode(pinI1,OUTPUT);//定义该接口为输出接口
  pinMode(pinI2,OUTPUT);
  pinMode(speedpin1,OUTPUT);
  pinMode(pinI3,OUTPUT);//定义该接口为输出接口
  pinMode(pinI4,OUTPUT);
  pinMode(speedpin2,OUTPUT);
  pinMode(receiverpin,INPUT);
  Serial,begin(9600).
  irrecv.enableIRIn();// 开始接收
}

void loop() 
{
   if (irrecv.decode(&results))
   {
      Serial.println(results.value, HEX);
     switch(results.value)
     {
     case ADVAN://>>键前进
       goForward(100);
       break;
     case BAC://<<键后退
       goBackward(100);
       break;
     case STO://>|键停止
       stopa();
       break;         
    default:
       delay(600);
     }
     irrecv.resume(); // 接收下一个值
   }
   delay(600);
}

void goForward(int a)//前进
{
analogWrite(speedpin1,a);//输入模拟值进行设定速度  
analogWrite(speedpin2,a);
digitalWrite(pinI1,LOW);//使直流电机（左）顺时针转 
digitalWrite(pinI2,HIGH);
digitalWrite(pinI3,LOW);//使直流电机（右）逆时针转 
digitalWrite(pinI4,HIGH);
delay(2000);
}

void goBackward(int b)//后退
{
analogWrite(speedpin1,b);//输入模拟值进行设定速度  
analogWrite(speedpin2,b);
digitalWrite(pinI1,HIGH);//使直流电机（左）逆顺时针转 
digitalWrite(pinI2,LOW);
digitalWrite(pinI3,HIGH);//使直流电机（右）顺时针转 
digitalWrite(pinI4,LOW);
delay(2000);
}

void stopa()//停止
{    
digitalWrite(pinI1,HIGH);//使直流电机（左）制动  
digitalWrite(pinI2,HIGH); 
digitalWrite(pinI3,HIGH);//使直流电机（右）制动 
digitalWrite(pinI4,HIGH);    
delay(2000);
}
