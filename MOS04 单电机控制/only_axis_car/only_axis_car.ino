int CHWM;
void setup() {
    TCCR1B = TCCR1B & 0b11111000 | 1; 
    TCCR0B = (TCCR0B & 0b11111000) | 2;
     pinMode(8,OUTPUT);//轴向小车电源通断输出口 // put your setup code here, to run once:
     pinMode(7,OUTPUT);//正反转输出口
     pinMode(9,OUTPUT);//PWM波输出口
     pinMode(5,OUTPUT);//PWM波输出口
     pinMode(2,INPUT_PULLUP);//正转输入 
     pinMode(3,INPUT_PULLUP);//反转输入 
     pinMode(A2,INPUT);//DSC08速度控制
}

void loop() {
    CHWM=map(analogRead(A2),0,1020,100,0);//获取轴动小车的PWM信号
     analogWrite(9,CHWM);//轴向小车PWM输出
      analogWrite(5,CHWM);//轴向小车PWM输出
     
    if(digitalRead(2)==0&digitalRead(3)==1){
              digitalWrite(8,1);
              digitalWrite(7,0);
          }
           if(digitalRead(3)==0&digitalRead(2)==1){
              digitalWrite(8,1);
              digitalWrite(7,1);
          }
          if(digitalRead(3)==0&digitalRead(2)==0){
              digitalWrite(8,0);
          }
           if(digitalRead(3)==1&digitalRead(2)==1){
              digitalWrite(8,0);
            }
}
