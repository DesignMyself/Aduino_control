int CHWM;
void setup() {
  pinMode(12,INPUT_PULLUP);//电机正转输入 
  pinMode(11,INPUT_PULLUP);//电机反转输入 
  pinMode(10,INPUT_PULLUP);//水泵通断控制
  pinMode(A1,INPUT);
  pinMode(7,OUTPUT);//电机正反转输出口
  pinMode(4,OUTPUT);//电机电源通断控制口
  pinMode(5,OUTPUT);//电机PWM调速控制口
  pinMode(8,OUTPUT);

}

void loop() {
  CHWM=map(analogRead(A1),0,1024,80,250);
  analogWrite(5,CHWM);
      car();
}
void car()
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
        if(digitalRead(10)==0){
          digitalWrite(8,1);
        }
        if(digitalRead(10)==1){
          digitalWrite(8,0);
        }
          
    
}
/*void auto1()
{
    int i;
    for(i=0;i<80;i++){
        up();
    }
     for(i=0;i<1;i++){
        stop1();
    }
    for(i=0;i<88;i++)
    {
      down();
    }
    for(i=0;i<1;i++){
        stop1();
    }
}
void up(){
    if(digitalRead(10)==0){
            digitalWrite(7,0);
            digitalWrite(4,1);
            delay(100);
    }
}
void down(){
  if(digitalRead(10)==0){
            digitalWrite(7,1);
            digitalWrite(4,1);
            delay(100);
    }

}
void stop1(){
  if(digitalRead(10)==0){
            digitalWrite(4,0);
            delay(100);
}
}
*/


