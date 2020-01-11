/*Include Software serial library*/
#include <SoftwareSerial.h>

/*Creating instance of software serial */
SoftwareSerial ArduinoSlave(2,3);

String answer;
String pres;

int light = 13;
int fan = 12;
int doorlock = 10;
int power = 11;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ArduinoSlave.begin(9600);
  pinMode(light,OUTPUT);
  pinMode(fan,OUTPUT);
  pinMode(doorlock,OUTPUT);
  pinMode(power,OUTPUT);

  pinMode(4,INPUT); //Light 
  pinMode(5,INPUT); //Fan
  pinMode(6,INPUT); //Power
  pinMode(7,INPUT); //DoorLock

  
}

void loop() {
  // put your main code here, to run repeatedly:
  //Read answer from slave
    while (ArduinoSlave.available()) {
      delay(10);  
      if (ArduinoSlave.available() >0) {
          char c = ArduinoSlave.read();  //gets one byte from serial buffer
          answer += c; //makes the string readString
        }
    }
  if(digitalRead(4)){
    digitalWrite(light,LOW);
    
  }else{
    digitalWrite(light,HIGH);
  }
  if(digitalRead(5)){
    digitalWrite(fan,LOW);
  }else{
    digitalWrite(fan,HIGH);
  }
  if(digitalRead(6)){
    digitalWrite(power,LOW);
  }else{
    digitalWrite(power,HIGH);
  }
  if(digitalRead(7)){
    ArduinoSlave.print("open");
    delay(1000);
  }else{
    //ArduinoSlave.print("close");
    //delay(1000);
  }
  
}
//void readSerialPort(){
//  while (Serial.available()) {
//  delay(10);  
//  if (Serial.available() >0) {
//      char c = Serial.read();  //gets one byte from serial buffer
//      msg += c; //makes the string readString
//    }
//  }
//  Serial.flush();
//}
