#include <Wire.h>

//we use variables naming the digital outputs/inputs
int Red = 5;
int Yellow = 7;
int Green = 8;

int Ped_Red = 4;
int Ped_Green = 3;

int status = 0;
int i, j;

int Current_State;
//int Button_Bus_pressed=0, Button_Ped_pressed=0;

void setup() //declaration of digital outputs
{
  pinMode(Green , OUTPUT);
  pinMode(Yellow , OUTPUT);
  pinMode(Red , OUTPUT);
  pinMode(Ped_Green , OUTPUT);
  pinMode(Ped_Red , OUTPUT);
  
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(ReceiveEvent);
  Serial.begin(9600);           // start serial for output
}
void ReceiveEvent (int howMany) {
  while (Wire.available()) {
    Current_State = Wire.read();    // read one character from the I2C
  }
}

void loop() {
switch(Current_State) {
/******** GreenState *********/
    case 0:
    digitalWrite(Green ,HIGH);
    digitalWrite(Ped_Red ,HIGH);
    for(i=0;i<=100;i++)
      delay(50);
    break;

   case 1:
   digitalWrite(Green ,0);
   digitalWrite(Yellow ,1);
    delay(1000);
    for(int j=0;j<=2;j++)
        {
        digitalWrite(Yellow ,1);
          delay(600);
        digitalWrite(Yellow ,0);
          delay(300);
        }
    break;

/********* Red State *********/
    case 2:
    digitalWrite(Green ,0);
    digitalWrite(Red ,1);
    for(j=0;j<=100;j++)
      delay(50);
    break;

/********* Ped Green State *********/
    case 3:
    digitalWrite(Red ,HIGH);
    digitalWrite(Green ,LOW);
    for(int k=0;k<=2;k++) { //for blinking
      digitalWrite(Ped_Red ,HIGH);
      delay(600);
      digitalWrite(Ped_Red ,LOW);
      delay(300);
    }
    digitalWrite(Ped_Green ,HIGH);
    delay(4000);
    for(int l=0;l<=2;l++) {
      digitalWrite(Ped_Green ,HIGH);
      delay(600);
      digitalWrite(Ped_Green ,LOW);
      delay(300);
    }
    break;

/********* Ped Red State ********/
    case 4:
    digitalWrite(Ped_Green ,LOW);
    digitalWrite(Ped_Red ,HIGH);
    break;

    case 5:
    digitalWrite(Ped_Green ,0);
    digitalWrite(Green ,0);
    for(int k=0;k<2;k++) {  //for blinking
      digitalWrite(Yellow ,1);
      delay(600);
      digitalWrite(Yellow ,0);
      delay(300);
    }

    case 6:
    digitalWrite(Green ,0);
    break;

    case 7:
      digitalWrite(Red ,0);  
      digitalWrite(Yellow ,1);
      for(i=0;i<=2;i++) {
       digitalWrite(Yellow ,1);
       delay(600);
       digitalWrite(Yellow ,0);
       delay(300);
     }
    break;
  }//switch bracket
}//void loop braket
