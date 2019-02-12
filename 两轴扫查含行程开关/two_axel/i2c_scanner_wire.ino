// --------------------------------------
// i2c_scanner
//
// Version 1
//    This program (or code that looks like it)
//    can be found in many places.
//    For example on the Arduino.cc forum.
//    The original author is not know.
// Version 2, Juni 2012, Using Arduino 1.0.1
//     Adapted to be as simple as possible by Arduino.cc user Krodal
// Version 3, Feb 26  2013
//    V3 by louarnold
// Version 4, March 3, 2013, Using Arduino 1.0.3
//    by Arduino.cc user Krodal.
//    Changes by louarnold removed.
//    Scanning addresses changed from 0...127 to 1...119,
//    according to the i2c scanner by Nick Gammon
//    http://www.gammon.com.au/forum/?id=10896
// Version 5, March 28, 2013
//    As version 4, but address scans now to 127.
//    A sensor seems to use address 120.
//
// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.
//

#include <Wire.h>

//use IIC2
//TwoWire WIRE2 (2,I2C_FAST_MODE);
//#define Wire WIRE2
#define regRead 0x00
#define regWrite 0x01
//register map
#define ABN_Addr     0x09
#define RAW_ANGLE_H8 0x0C
#define RAW_ANGLE_L8 0x0D
#define ZPOS_H8      0x01
#define ZPOS_L8      0x02
#define CONF_H8		 0x07
#define CONF_L8 	 0x08
#define PUSHTHR      0x0A
#define BURN         0xFF
//
#define BURN_ANGLE   0x80
#define BURN_Setting 0x40


#define ABNRate_8 		0 //8
#define ABNRate_16 		1 //16
#define ABNRate_32 		2 //32
#define ABNRate_64 		3 //64
#define ABNRate_128 	4 //128
#define ABNRate_256 	5 //256
#define ABNRate_512 	6 //512
#define ABNRate_1024 	7 //1024 


byte vailableAddress;
byte frame[4];
byte isHead =0,isFinish =0;
byte inByte,byteCount=0;

byte byRAWANGLE_H8,byRAWANGLE_L8;
byte byZPOS_H8,byZPOS_L8;
byte byCONF_H8,byCONF_L8;
byte byPUSHTHR;


void setup() {
  
  Serial1.begin(115200);
  Wire.begin();
  Serial1.println("\nI2C Scanner");
  findDevices();
  //zeroPosition 
  zeroPosition();
}


void loop() {  
  if(Serial1.available()>0)
  {
    inByte = Serial1.read();
    if(isHead)
    {
      byteCount ++;
      frame[byteCount]= inByte;
      if(byteCount>=3)
      {
        isFinish =1;
      }
    }
    if(inByte == 0x5A)
    {
      isHead = 1;
      byteCount=0;
      frame[byteCount]= inByte;
    }
    if(isFinish)
    {
      isFinish =0;
      isHead = 0;
      byteCount=0;
      //
      if(frame[1] == regRead)
      {
       // ReadFromI2C(vailableAddress,frame[2],frame[3]);
      }
      else if (frame[1] == regWrite)
      {
       // WriteToI2C(vailableAddress,frame[2],frame[3]);
      }
    }
  }

  
 // ReadFromI2C(vailableAddress,0x1B,2);
//  WriteToI2C(vailableAddress,0x07,0x1A);
//  delay(5);
//  WriteToI2C(vailableAddress,0x08,0x00);
//  delay(5);
//  WriteToI2C(vailableAddress,0x09,0x07);

  //WriteToI2C(vailableAddress,0x09,0x02);
  //delay(1000);           // wait 5 seconds for next scan
  //delay(2000);           // wait 5 seconds for next scan
}

byte findDevices()
{
    byte error, address;
    int nDevices;
    nDevices = 0;
  for(address = 1; address < 127; address++) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.

    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    
    if (error == 0) {
      Serial1.print("I2C device found at address 0x");
      if (address < 16) 
        Serial1.print("0");
      Serial1.println(address, HEX);
      vailableAddress = address;
      nDevices++;
    }
    else if (error == 4) {
      Serial1.print("Unknown error at address 0x");
      if (address < 16) 
        Serial1.print("0");
      Serial1.println(address, HEX);
    }    
  }
  if (nDevices == 0)
    Serial1.println("No I2C devices found");
  else
    Serial1.println("done");
    return address;
}
// Function used to write to I2C:
void WriteToI2C(int device, byte address, byte val)
{
    Wire.beginTransmission(device);
    Wire.write(address);
    Wire.write(val);
    Wire.endTransmission();
    Serial1.println("Write finish"); 
}
 
/* // Function to read from I2C
void ReadFromI2C(int device, byte address, byte bytesToRead)
{
    char c;
    Wire.beginTransmission(device);
    Wire.write(address);
    Wire.endTransmission();
   
    //Wire.beginTransmission(device);
    Wire.requestFrom(device, bytesToRead);
    delay(5);
    char i = 0;  
    Serial1.println("read reg:"); 
    while ( Wire.available() )
    {
        c = Wire.read();
        if(c < 16)
          Serial1.print("0");
        Serial1.println(c, HEX);
    }   
    //Wire.endTransmission();
} */
byte readRegisterValueI2C(int device,byte reg_addr)
{
	byte value=0;
	Wire.beginTransmission(device);
    Wire.write(reg_addr);
    Wire.endTransmission();
	
	Wire.beginTransmission(device);
    Wire.requestFrom(device, 1);
	delay(5);
	while (Wire.available())
	{
		value = Wire.read();
		Serial1.print("register");
    Serial1.println(reg_addr, HEX);
		Serial1.print("Value:");
		Serial1.println(value, HEX);
	}
	Wire.endTransmission();
	return value;
}
//zero position and resolution programming procedure;
void zeroPosition()
{
  //config the desired number of position using ABN(3:0);
  WriteToI2C(vailableAddress,ABN_Addr,ABNRate_1024);
  //读取 RAW ANGLE 
  byRAWANGLE_H8 = readRegisterValueI2C(vailableAddress,RAW_ANGLE_H8);
  byRAWANGLE_L8 = readRegisterValueI2C(vailableAddress,RAW_ANGLE_L8);
  //计算补偿值用来调整机械网络和编码器角度。
  //将补偿值添加如ZPOS
  byZPOS_H8 = byRAWANGLE_H8;
  byZPOS_L8 = byRAWANGLE_L8;
  WriteToI2C(vailableAddress,ZPOS_H8,byZPOS_H8);
  WriteToI2C(vailableAddress,ZPOS_L8,byZPOS_L8);
  //wait at least 1ms
  delay(5);
  //将所需配置写入配置寄存器 CONF AND PUSHTHR
  //
  byte PM =0;  			//Power Mode :00 = NOM, 01 = LPM1, 10 = LPM2, 11 = LPM3
  byte HYST = 0;		//Hysteresis :00 = OFF, 01 = 1 LSB, 10 = 2 LSBs, 11 = 3 LSBs
  byte SF =0;           //Slow Filter:00 = 16x(1); 01 = 8x; 10 = 4x; 11 = 2x
  byte FTH =0;			//Fast Filter Threshold :000 = slow filter only, 001 = 6 LSBs, 010 = 7 LSBs, 011 = 9 LSBs,100 = 18 LSBs, 101 = 21 LSBs, 110 = 24 LSBs, 111 = 10 LSBs
  byte WD =0;           //Watchdog Timer:0 = OFF, 1 = ON (automatic entry into LPM3 low-power mode enabled)
  
  byCONF_H8 = (WD<<5) | (FTH<<2) | SF ;
  byCONF_L8 = (HYST<<2) | PM;
  
  WriteToI2C(vailableAddress,CONF_H8,byCONF_H8);
  WriteToI2C(vailableAddress,CONF_L8,byCONF_L8);
  
  //WriteToI2C(vailableAddress,PUSHTHR,);
  delay(5);
  //继续执行，固化配置
  WriteToI2C(vailableAddress,BURN,BURN_ANGLE);
  delay(5);
  WriteToI2C(vailableAddress,BURN,BURN_Setting);
  delay(5);
  //验证固化配置是否正常
  //依次将指令 0x01,0x11,0x10 写入寄存器 0xFF 加载实际的OTP值。
  WriteToI2C(vailableAddress,BURN,0x01);
  WriteToI2C(vailableAddress,BURN,0x11);
  WriteToI2C(vailableAddress,BURN,0x10);  
  //读取ABN的值，看是否成功写入。
  byte valABN = readRegisterValueI2C(vailableAddress,ABN_Addr);
  //读取并验证永久编程寄存器以验证 BURN_SETTINGS 和 BURN_ANGLE 命令是否成功。
  //在新的开机周期后再次读取并验证永久编程寄存器
}




