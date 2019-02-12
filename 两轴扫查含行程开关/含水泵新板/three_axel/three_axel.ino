int CHWM;
int JPWM;
int M1W=4;//DSC08小车电源输出
int M1F=2;//小车前进控制
int M1B=3;//小车后退控制
int PWM1=5;//小车PWM输出
int M1ST=6;//小车刹车输出
int M1CC=7;//小车前过后退输出
int M2W=8;//小车2电源输出
int PWM2=9;//小车2PWM输出
int M2CC=10;//小车2正反向输出
int M3F=11;//水泵开关控制
int M3W=12;//小泵电源输出
int M2B=14;//小车2后退控制 
int PWM2R=15;//小车2PWM读取控制
int PWM1R=16;//小车1PWM读取控制
int M2F=17;//小车2前进控制 
int SEN2=19;//外接传感器
int SEN1=20;//外接传感器
void setup() {
  /************遥控输入 *********************/
  pinMode(M1F,INPUT_PULLUP);//DSC08正转输入 
  pinMode(M1B,INPUT_PULLUP);//DSC08反转输入 
  pinMode(M2F,INPUT_PULLUP);//X轴正转输入
  pinMode(M2B,INPUT_PULLUP);//x轴反转输入
  pinMode(M3F,INPUT_PULLUP);//水泵开关
  pinMode(PWM1R,INPUT);//DSC08速度控制
  pinMode(PWM2R,INPUT);//轴向小车速度控制

  /***************传感器控制口**********************/
  pinMode(SEN1,INPUT_PULLUP);//小车前方左边的传感器A3
  pinMode(SEN2,INPUT_PULLUP);//小车前方右边的传感器A4
    /**********************************************/
  pinMode(M2CC,OUTPUT);//X轴正反转输出口
  pinMode(M1CC,OUTPUT);//DSC08正反转输出口
  pinMode(M2W,OUTPUT);//X轴电源通断输出口
   pinMode(M1ST,OUTPUT);//小车刹车
   pinMode(M1W,OUTPUT);//DSC08电源通断输出口
  pinMode(PWM2,OUTPUT);//X轴波输出口
  pinMode(PWM1,OUTPUT);//DSC08PWM波输出口
  pinMode(M3W,OUTPUT);//水泵电源输出
  
  // put your setup code here, to run once:

}

void loop() {
  JPWM=map(analogRead(PWM1R),0,1024,0,200);//获取DSC08的PWM信号
  CHWM=map(analogRead(PWM2R),0,1024,200,0);//获取轴动小车的PWM信号
  analogWrite(PWM1,CHWM);//轴向小车PWM输出
  analogWrite(PWM2,JPWM);//DSC08PWM输出
  car();
}

void car()
{
   DSC08();
   SC0021();
   PUMB();
}
//DSC08手动模式
void DSC08()
{
    if(digitalRead(M1F)==0&digitalRead(M1B)==1){
              digitalWrite(M1W,1);//小车电源输出
              digitalWrite(M1ST,0);//小车刹车输出
              digitalWrite(M1CC,0);//小车正向行走
          }
           if(digitalRead(M1B)==0&digitalRead(M1F)==1){
              digitalWrite(M1W,1);//小车电源输出
              digitalWrite(M1CC,1);//小车反向行走
          }
          if(digitalRead(M1F)==0&digitalRead(M1B)==0){
              digitalWrite(M1W,0);
              digitalWrite(M1ST,1);//小车刹车输出
               digitalWrite(M1CC,0);//把三极管也同时关闭
          }
           if(digitalRead(11)==1&digitalRead(12)==1){
                 digitalWrite(M1W,0);
                 digitalWrite(M1ST,1);//小车刹车输出
                 digitalWrite(M1CC,0);//把三极管也同时关闭
            }
 
        

}

void SC0021()
{
   if(digitalRead(M2F)==0&digitalRead(M2B)==1&digitalRead(SEN2)==1){
              digitalWrite(M2W,1);
              digitalWrite(M2CC,0);//X轴正向行走
          }
           if(digitalRead(M2F)==1&digitalRead(M2B)==0&digitalRead(SEN1)==1){
              digitalWrite(M2W,1);
              digitalWrite(M2CC,1);//X轴反向行走
          }
          if(digitalRead(M2F)==0&digitalRead(M2B)==0){
              digitalWrite(M2W,0);
              digitalWrite(M2CC,0);//停止
          }
           if(digitalRead(M2F)==1&digitalRead(M2B)==1){
              digitalWrite(M2W,0);
              digitalWrite(M2CC,0);//停止
            }
             if(digitalRead(SEN1)==0&digitalRead(SEN2)==0){
             digitalWrite(M2W,0);
              digitalWrite(M2CC,0);//停止
            }
             if(digitalRead(SEN1)==0&digitalRead(SEN2)==1&digitalRead(M2F)==1&digitalRead(M2B)==0){
              digitalWrite(M2W,0);
              digitalWrite(M2CC,0);//停止
          }
          if(digitalRead(SEN1)==1&digitalRead(SEN2)==0&digitalRead(M2F)==0&digitalRead(M2B)==1){
              digitalWrite(M2W,0);
              digitalWrite(M2CC,0);//停止
          }
}

void PUMB()
{
  if(digitalRead(M3F==0))
  {   
    digitalWrite(M3W,1);

  }else
  {
        digitalWrite(M3W,1);
    
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

