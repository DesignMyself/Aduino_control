
void setup() {
   pinMode(8,OUTPUT);//轴向小车电源通断输出口
  pinMode(4,OUTPUT);//DSC08电源通断输出口
  
  pinMode(6,OUTPUT);//DSC08刹车
  pinMode(2,INPUT_PULLUP);//DSC08正转输入 
  pinMode(3,INPUT_PULLUP);//DSC08反转输入 
  pinMode(A4,INPUT_PULLUP);//轴向小车正转输入
  pinMode(A1,INPUT_PULLUP);//轴向小车反转输入
   pinMode(A0,INPUT_PULLUP);//自动控制输出口
  pinMode(A2,INPUT);//DSC08速度控制
  pinMode(A3,INPUT);//轴向小车速度控制
  pinMode(7,OUTPUT);//DSC08正反转输出口
  pinMode(10,OUTPUT);//轴向小车正反转输出口   
  pinMode(5,OUTPUT);//DSC08_PWM波输出口
  pinMode(9,OUTPUT);//轴向小车PWM波输出口
   pinMode(12,OUTPUT);
}
int CHWM;
int JPWM;
//   digitalWrite(4,1);//初始化小车的初始为停
//   digitalWrite(6,1);//DSC08初始处于刹车状态
//   digitalWrite(7,1);//初始化DSC08的方向
//    digitalWrite(10,1);//初始化轴向小车的方向
//    digitalWrite(8,1);//初始化轴向小车初始为停
//   digitalWrite(12,1);//初始化水泵停止
void loop() {
  JPWM=map(analogRead(A3),0,1024,80,250);//获取DSC08的PWM信号
  CHWM=map(analogRead(A2),0,1024,80,250);//获取轴动小车的PWM信号
  analogWrite(9,CHWM);//轴向小车PWM输出
  analogWrite(5,JPWM);//DSC08PWM输出
if(digitalRead(A0)==1)//手动模式
    {
      car();
   }
 if(digitalRead(A0)==0)//自动模式
 {
      autocar();

 }
  
 //auto1(); // put your main code here, to run repeatedly:

}
void car()
{
   DSC08();
   SC0021();
}
//DSC08手动模式
void DSC08()
{
    if(digitalRead(2)==0&digitalRead(3)==1){
              delay(50);
              digitalWrite(4,0);//开启电机
              digitalWrite(6,0);//DSC08关闭刹车状态
              digitalWrite(7,0);//反向
          }
           if(digitalRead(2)==1&digitalRead(3)==0){
              delay(50);
              digitalWrite(4,0);//开启电机
              digitalWrite(6,0);//DSC08关闭刹车状态
              digitalWrite(7,1);
          }
          if(digitalRead(2)==0&digitalRead(3)==0){
              digitalWrite(4,1);
              digitalWrite(6,1);//DSC08关闭刹车状态
              digitalWrite(7,1);//反向
          }
           if(digitalRead(2)==1&digitalRead(3)==1){
             digitalWrite(4,1);
              digitalWrite(6,1);//DSC08关闭刹车状态
              digitalWrite(7,1);//反向
            }
 
        

}

void SC0021()
{
   if(digitalRead(A4)==0&digitalRead(A1)==1){
              digitalWrite(8,0);
              digitalWrite(10,1);
          }
           if(digitalRead(A4)==1&digitalRead(A1)==0){
              digitalWrite(8,0);
              digitalWrite(10,0);
          }
          if(digitalRead(A4)==0&digitalRead(A1)==0){
              digitalWrite(8,1);
              digitalWrite(10,1);
          }
           if(digitalRead(A4)==1&digitalRead(A1)==1){
              digitalWrite(8,1);
              digitalWrite(10,1);
            }
}
void autocar()
{
    int i;
    for(i=0;i<80;i++){
        up();
    }
     for(i=0;i<1;i++){
        stop1();
    }
    for(i=0;i<100;i++)
    {
      down();
    }
    for(i=0;i<1;i++){
        stop1();
    }
}
void up(){
    if(digitalRead(A0)==0){
            digitalWrite(8,0);
            digitalWrite(6,0);//DSC08关闭刹车状态
            digitalWrite(4,0);
            digitalWrite(7,1);
             digitalWrite(10,0);
            delay(100);
    }
}
void down(){
  if(digitalRead(A0)==0){
            digitalWrite(8,0);
            digitalWrite(6,0);//DSC08关闭刹车状态
            digitalWrite(4,0);
            digitalWrite(7,0);
             digitalWrite(10,1);
            delay(100);
    }

}
void stop1(){
  if(digitalRead(A0)==0){
            digitalWrite(4,1);
            digitalWrite(8,1);
             digitalWrite(6,1);//DSC08关闭刹车状态
            delay(100);
}
}



