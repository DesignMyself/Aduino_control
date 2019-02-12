int CHWM;
int JPWM;
void setup() {
  pinMode(12,INPUT_PULLUP);//DSC08正转输入 
  pinMode(11,INPUT_PULLUP);//DSC08反转输入 
  pinMode(10,INPUT_PULLUP);//轴向小车正转输入
  pinMode(A0,INPUT_PULLUP);//轴向小车反转输入
   pinMode(A3,INPUT_PULLUP);//自动控制输出口
  pinMode(A2,INPUT);//DSC08速度控制
  pinMode(A1,INPUT);//轴向小车速度控制
  pinMode(7,OUTPUT);//DSC08正反转输出口
  pinMode(9,OUTPUT);//轴向小车正反转输出口
  pinMode(4,OUTPUT);//DSC08电源通断输出口
   pinMode(8,OUTPUT);//轴向小车电源通断输出口
  pinMode(5,OUTPUT);//DSC08_PWM波输出口
  pinMode(6,OUTPUT);//轴向小车PWM波输出口
  pinMode(A3,INPUT_PULLUP);//自动控制输出口
  
  // put your setup code here, to run once:

}

void loop() {
  JPWM=map(analogRead(A2),0,1024,0,255);//获取DSC08的PWM信号
  CHWM=map(analogRead(A1),0,1024,255,30);//获取轴动小车的PWM信号
  analogWrite(6,CHWM);//轴向小车PWM输出
  analogWrite(5,JPWM);//DSC08PWM输出
if(digitalRead(A3)==1)//手动模式
    {
      car();
   }
 if(digitalRead(A3)==0)//自动模式
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
    if(digitalRead(12)==0&digitalRead(11)==1){
              digitalWrite(4,1);
              digitalWrite(7,0);
          }
           if(digitalRead(11)==0&digitalRead(12)==1){
              digitalWrite(4,1);
              digitalWrite(7,1);
          }
          if(digitalRead(11)==0&digitalRead(12)==0){
              digitalWrite(4,0);
          }
           if(digitalRead(11)==1&digitalRead(12)==1){
              digitalWrite(4,0);
            }
 
        

}

void SC0021()
{
   if(digitalRead(10)==0&digitalRead(A0)==1){
              digitalWrite(8,1);
              digitalWrite(9,1);
          }
           if(digitalRead(A0)==0&digitalRead(10)==1){
              digitalWrite(8,1);
              digitalWrite(9,0);
          }
          if(digitalRead(A0)==0&digitalRead(10)==0){
              digitalWrite(8,0);
          }
           if(digitalRead(A0)==1&digitalRead(10)==1){
              digitalWrite(8,0);
            }
}
void autocar()
{
    int i;
    for(i=0;i<60;i++){
        up();
    }
     for(i=0;i<5;i++){
        stop1();
    }
    for(i=0;i<60;i++)
    {
      down();
    }
    digitalWrite(4,0);
    for(i=0;i<1;i++)
    {
      zxdowmmore();
    }
   
    for(i=0;i<5;i++){
        stop1();
    }
}
void up(){
    if(digitalRead(A3)==0){
            digitalWrite(8,1);//轴向小车
            digitalWrite(9,1);
            
            digitalWrite(4,1);
             digitalWrite(7,0);
            delay(100);
    }
}
void down(){
  if(digitalRead(A3)==0){
            digitalWrite(8,1);
            digitalWrite(9,0);
            
            digitalWrite(4,1);
             digitalWrite(7,1);
            delay(100);
    }
}
void zxdowmmore(){
 if(digitalRead(A3)==0){
            digitalWrite(8,1);
            digitalWrite(9,0);
            delay(100);
}
}
void stop1(){
  if(digitalRead(A3)==0){
            digitalWrite(4,0);
            digitalWrite(8,0);
            delay(100);
}
}



