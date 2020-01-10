/*

RFID PINOUT:

RC522 MODULE    Uno/Nano     MEGA
SDA             D10          D9
SCK             D13          D52
MOSI            D11          D51
MISO            D12          D50
IRQ             N/A          N/A
GND             GND          GND
RST             D9           D8
3.3V            3.3V         3.3V

Servo PINOUT:
Servo Signal   Digital Pin 8

Bluetooth Module
RX  D3
TX  D2
*

* Include the standard Arduino SPI library */
#include <SPI.h>
/* Include the RFID library */
#include <RFID.h>
/*Include software serial*/
#include <SoftwareSerial.h>
/*Include servo library*/
#include <Servo.h>

/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#define SDA_DIO 10
#define RESET_DIO 9
/* Create an instance of the RFID library */
RFID RC522(SDA_DIO, RESET_DIO); 
/*Create a soft Serial port*/
SoftwareSerial ArduinoMaster(2,3);
String msg;
/*Create Servo Instance*/
Servo doorlock;

void setup()
{ 
  Serial.begin(9600);
  /* Enable Bluetooth module to comunicate*/
  ArduinoMaster.begin(9600);
  /* Enable the SPI interface */
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC522.init();
  /*Initializing Doorlock Servo*/
  doorlock.attach(8);
  doolock.write(0);
}

void loop()
{
  readSerialPort(); // Consitantly checking incoming text from Phase Three machine.
  /* Temporary loop counter */
  byte i=0;
  byte j=0;
  byte k=0;
  int ID;

  /* Has a card been detected? */
  if (RC522.isCard())
  {
    /* If so then get its serial number */
    RC522.readCardSerial();
    /* Output the serial number to the UART */
    ID=RC522.serNum[0];
    /*Matching with existing card*/
    if(ID == 1616){
      if(doorlock.read()==0) doorlock.write(90); // Changing door lock open to close
      else if(doorlock.read()==90) doorlock.write(0); // Changing doorlock close to open
      else doorlock.write(0); //Default case open 
    }
    else if(ID == 183183){
      if(doorlock.read()==0) doorlock.write(90); // Changing door lock open to close
      else if(doorlock.read()==90) doorlock.write(0); // Changing doorlock close to open
      else doorlock.write(0); //Default case open 
    }
  }
  delay(1000);

  if(msg!=""){
    if(msg=="open"){
      doorlock.write(0); // Changing doorlock close to open
      ArduinoMaster.print("done"); //Sending confirmation into Phase Three machine..
    }else if(msg=="close"){
      doorlock.write(90); // Changing door lock open to close
      ArduinoMaster.print("done"); //Sending confirmation into Phase Three machine..
    }
    msg="";
  }
  
  
}


//Incoming text xhecking function ....
void readSerialPort(){
  while (ArduinoMaster.available()) {
  delay(10); 
  if (ArduinoMaster.available() >0) {
  char c = ArduinoMaster.read();  //gets one byte from serial buffer
  msg += c; //makes the string readString
  }
  }
  ArduinoMaster.flush();
}
