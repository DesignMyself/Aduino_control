int CHWM;
int JPWM;
void setup() {
  /************遥控输入 *********************/
  pinMode(12,INPUT_PULLUP);//DSC08正转输入 
  pinMode(11,INPUT_PULLUP);//DSC08反转输入 
  pinMode(10,INPUT_PULLUP);//X轴正转输入
  pinMode(A0,INPUT_PULLUP);//x轴反转输入
  pinMode(A2,INPUT);//DSC08速度控制
  pinMode(A1,INPUT);//轴向小车速度控制

  /***************传感器控制口**********************/
  pinMode(A3,INPUT_PULLUP);//小车前方左边的传感器
  pinMode(A4,INPUT_PULLUP);//小车前方右边的传感器
    /**********************************************/
  pinMode(7,OUTPUT);//X轴正反转输出口
  pinMode(9,OUTPUT);//DSC08正反转输出口
  pinMode(4,OUTPUT);//X轴电源通断输出口
   pinMode(8,OUTPUT);//DSC08电源通断输出口
  pinMode(5,OUTPUT);//X轴波输出口
  pinMode(6,OUTPUT);//DSC08PWM波输出口

  
  // put your setup code here, to run once:

}

void loop() {
  JPWM=map(analogRead(A2),0,1024,0,200);//获取DSC08的PWM信号
  CHWM=map(analogRead(A1),0,1024,200,0);//获取轴动小车的PWM信号
  analogWrite(5,CHWM);//轴向小车PWM输出
  analogWrite(6,JPWM);//DSC08PWM输出
  car();
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
              digitalWrite(8,1);//小车电源输出
              digitalWrite(9,0);//小车正向行走
          }
           if(digitalRead(11)==0&digitalRead(12)==1){
              digitalWrite(8,1);//小车电源输出
              digitalWrite(9,1);//小车反向行走
          }
          if(digitalRead(11)==0&digitalRead(12)==0){
              digitalWrite(8,0);
               digitalWrite(9,0);//把三极管也同时关闭
          }
           if(digitalRead(11)==1&digitalRead(12)==1){
              digitalWrite(8,0);
               digitalWrite(9,0);//把三极管也同时关闭
            }
 
        

}

void SC0021()
{
   if(digitalRead(10)==0&digitalRead(A0)==1&digitalRead(A4)==1){
              digitalWrite(4,1);
              digitalWrite(7,0);//X轴正向行走
          }
           if(digitalRead(10)==1&digitalRead(A0)==0&digitalRead(A3)==1){
              digitalWrite(4,1);
              digitalWrite(7,1);//X轴反向行走
          }
          if(digitalRead(A0)==0&digitalRead(10)==0){
              digitalWrite(4,0);
              digitalWrite(7,0);//停止
          }
           if(digitalRead(A0)==1&digitalRead(10)==1){
              digitalWrite(4,0);
              digitalWrite(7,0);//停止
            }
             if(digitalRead(A3)==0&digitalRead(A4)==0){
              digitalWrite(4,0);
              digitalWrite(7,0);//停止
            }
             if(digitalRead(A3)==0&digitalRead(A4)==1&digitalRead(10)==1&digitalRead(A0)==0){
              digitalWrite(4,0);
              digitalWrite(7,0);//停止
          }
          if(digitalRead(A3)==1&digitalRead(A4)==0&digitalRead(10)==0&digitalRead(A0)==1){
              digitalWrite(4,0);
              digitalWrite(7,0);//停止
          }
}
//void autocar()
//{
//    int i;
//    for(i=0;i<80;i++){
//        up();
//    }
//     for(i=0;i<1;i++){
//        stop1();
//    }
//    for(i=0;i<100;i++)
//    {
//      down();
//    }
//    for(i=0;i<1;i++){
//        stop1();
//    }
//}
//void up(){
//    if(digitalRead(A3)==0){
//            digitalWrite(8,1);
//            digitalWrite(4,1);
//            digitalWrite(9,0);
//             digitalWrite(7,0);
//            delay(100);
//    }
//}
//void down(){
//  if(digitalRead(A3)==0){
//            digitalWrite(8,1);
//            digitalWrite(4,1);
//            digitalWrite(9,1);
//             digitalWrite(7,1);
//            delay(100);
//    }
//
//}
//void stop1(){
//  if(digitalRead(A3)==0){
//            digitalWrite(4,0);
//            digitalWrite(8,0);
//            delay(100);
//}
//}
//
//

