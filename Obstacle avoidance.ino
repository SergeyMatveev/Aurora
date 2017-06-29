#include <Servo.h>

Servo headservo;  // 头部舵机对象

const int EchoPin=2;//超声波信号输入
const int TrigPin=3;//超声波控制信号输出

const int in1=4;//直流电机正反转信号输出
const int in2=5;
const int in3=6;
const int in4=7;

const int HeadServopin=9;//舵机信号输出

int currDist=10;//距离


void setup(){

Serial.begin(9600);//开始串行监测

pinMode(EchoPin,INPUT);//设置2号引脚为输入
for (int i=3;i<=7;i++){
pinMode(i,OUTPUT);//设置3到7号引脚为输出
}
pinMode(HeadServopin,OUTPUT);//设置9、10、11引脚为输出

headservo.attach(HeadServopin);//舵机接口

headservo.write(150);//启动缓冲活动头部
delay(2000);
headservo.write(20);
delay(2000);
}

//主程序
void loop(){

currDist=MeasuringDistance();//读取超声波测得的距离

if(currDist>20){
nodanger();
}
else if(currDist<10){
backup();
}
else{
whichway();
}
}

//超声波测距
long MeasuringDistance() {
long duration;
pinMode(TrigPin, OUTPUT);
digitalWrite(TrigPin, LOW);
delayMicroseconds(2);
digitalWrite(TrigPin, HIGH);
delayMicroseconds(10);
digitalWrite(TrigPin, LOW);

pinMode(EchoPin, INPUT);
duration = pulseIn(EchoPin, HIGH);

return duration / 58;
}

//无障碍前进
void nodanger(){
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW); 
return;
}

//有障碍后退
void backup(){
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
return;
}

//选择路线
void whichway(){
totalhalt();// 停车且调整探头朝向正前方

headservo.write(20);
delay(1000);
int lDist = MeasuringDistance();   // 把左边探测到的数值赋值给lDdist

totalhalt();// 停车且调整探头朝向正前方

headservo.write(120);
delay(1000);
int rDist = MeasuringDistance();   // 把右边探测到的数值赋值给rDdist

totalhalt();// 恢复探测头

if(lDist < rDist){
    body_lturn();
  }
  else{
    body_rturn();
  }
  return;
}

//停车且调整探头朝向正前方
void totalhalt(){
digitalWrite(in1, HIGH);
digitalWrite(in2, HIGH);
digitalWrite(in3, HIGH);
digitalWrite(in4, HIGH);
headservo.write(70);  // 使得探头朝向正前方
return;
delay(1000);
}

//左转
void body_lturn() {
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
delay(1500);
totalhalt();
}  

//右转
void body_rturn() {
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
delay(1500);
totalhalt();
}  
