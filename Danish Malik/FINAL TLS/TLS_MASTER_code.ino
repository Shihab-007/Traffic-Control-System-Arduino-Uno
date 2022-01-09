#include <Wire.h>

//we use variables naming the digital outputs/inputs
#define Red 5
int Yellow = 7;
int Green = 8;

int Ped_Red = 4;
int Ped_Green = 3;

int Button_Ped = 2;
int Button_Bus = 6;

int Delay_Two_Seconds = 2000; //we use a variable for the delay 2 seconds

int status = 0;

int i = 0, j = 0;

const int Green_State = 0;
const int Yellow_State = 1;
const int Red_State = 2;
const int Ped_Red_State = 3;
const int Ped_Green_State = 4;

int Current_State = Green_State, Button_Bus_pressed=0, Button_Ped_pressed=0;

void setup() //declaration of digital outputs
{
  Serial.begin(9600);
  pinMode(Green , OUTPUT);
  pinMode(Yellow , OUTPUT);
  pinMode(Red , OUTPUT);
  pinMode(Ped_Green , OUTPUT);
  pinMode(Ped_Red , OUTPUT);
  pinMode(Button_Bus, INPUT);
  pinMode(Button_Ped, INPUT);
  Wire.begin();
}
void loop() {
  // digitalWrite(Green ,HIGH);
  Serial.println("Turn Pedestrien Red  on ");
  switch(Current_State) {
/******** GreenState ********/
    case Green_State:
    Wire.beginTransmission(8); // transmit to device #9
    Wire.write(0); // sends current state value
    Wire.endTransmission();    // stop transmitting
    digitalWrite(Green ,HIGH);
    digitalWrite(Ped_Red ,HIGH);
    for(i=0;i<=100;i++) {
      delay(50); 
      Button_Bus_pressed = digitalRead(Button_Bus);
      Button_Ped_pressed = digitalRead(Button_Ped);
      Serial.println(Button_Bus_pressed);
      Serial.println(Button_Ped_pressed);
      if(Button_Ped_pressed == 1 && Button_Bus_pressed == 1) {
        Current_State = Ped_Green_State;
        Wire.beginTransmission(8); // transmit to device #9
        Wire.write(5); // sends current state value
        Wire.endTransmission();    // stop transmitting
        Serial.println("Pedestrienlight become Green ");
        digitalWrite(Ped_Green ,0);
        digitalWrite(Green ,0);
        for(int k=0;k<2;k++) {  //for blinking
          digitalWrite(Yellow ,1);
          delay(600);
          digitalWrite(Yellow ,0);
          delay(300);
          }
          // digitalWrite(Ped_Red ,0);
        break;
      }
      else if(Button_Ped_pressed==1 && Button_Bus_pressed==0) {
        Current_State = Ped_Green_State;
        Serial.println("Pedestrienlight become Green ");
        Wire.beginTransmission(8); // transmit to device #9
        Wire.write(5); // sends current state value
        Wire.endTransmission();    // stop transmitting
        digitalWrite(Ped_Green ,0);
        digitalWrite(Green ,0);
        for(int i=0;i<2;i++) {  //for blinking
          digitalWrite(Yellow ,1);
          delay(600);
          digitalWrite(Yellow ,0);
          delay(300);
        }
      //delay(5000);
      //digitalWrite(Ped_Red ,0);
      break; 
    }
    else if(i==100) {
      Current_State = Yellow_State;
      Wire.beginTransmission(8); // transmit to device #9
      Wire.write(1); // sends current state value
      Wire.endTransmission();    // stop transmitting
      digitalWrite(Green ,0);
      break;
    }
    else if(Button_Ped_pressed==0 && Button_Bus_pressed==1) {
      Current_State = Yellow_State;
      Serial.println("Pedestrienlight become Red ");
      digitalWrite(Green ,0);
      Wire.beginTransmission(8); // transmit to device #9
      Wire.write(1); // sends current state value
      Wire.endTransmission();    // stop transmitting
      break;
    }
   }  //for loop braket
   digitalWrite(Red ,LOW);
   break;
   
   case Yellow_State:
   digitalWrite(Yellow ,1);
   Wire.beginTransmission(8); // transmit to device #9
    Wire.write(1); // sends current state value
    Wire.endTransmission();    // stop transmitting
    delay(1000);
    Current_State = Red_State;
    for(int j=0;j<=2;j++)
        {
        digitalWrite(Yellow ,1);
          delay(600);
        digitalWrite(Yellow ,0);
          delay(300);
        }
    break;

/******** Red State ********/
    case Red_State:
    digitalWrite(Green ,0);
    digitalWrite(Red ,1);
    Wire.beginTransmission(8); // transmit to device #9
    Wire.write(2); // sends current state value
    Wire.endTransmission();    // stop transmitting
    for( j=0;j<=100;j++) {
      delay(50);
      if(digitalRead(Button_Ped)==1) {
        digitalWrite(Green ,0);
        Wire.beginTransmission(8); // transmit to device #9
        Wire.write(6); // sends current state value
        Wire.endTransmission();    // stop transmitting
        //digitalWrite(Red ,1);
        Current_State = Ped_Green_State;
        break; 
      }//if statement block
      else if(j == 100) {
          Wire.beginTransmission(8); // transmit to device #9
          Wire.write(7); // sends current state value
          Wire.endTransmission();    // stop transmitting
          digitalWrite(Red ,0);  
          digitalWrite(Yellow ,1);
        for(int i=0;i<=2;i++) {
          digitalWrite(Yellow ,1);
          delay(600);
          digitalWrite(Yellow ,0);
          delay(300);
        }
        Current_State = Green_State;
        break;
      }
    }//brackets of forloop
    break;

/******** Ped Green State ********/
    case Ped_Green_State:
    Wire.beginTransmission(8); // transmit to device #9
    Wire.write(3); // sends current state value
    Wire.endTransmission();    // stop transmitting
    digitalWrite(Red ,HIGH);
    digitalWrite(Green ,LOW);
    for(int k=0;k<=2;k++) { //for blinking
      digitalWrite(Ped_Red ,HIGH);
      delay(600);
      digitalWrite(Ped_Red ,LOW);
      delay(350);
    }
    digitalWrite(Ped_Green ,HIGH);
    delay(4000);
    for(int l=0;l<=2;l++) {
      digitalWrite(Ped_Green ,HIGH);
      delay(600);
      digitalWrite(Ped_Green ,LOW);
      delay(300);
    }
    Current_State = Ped_Red_State;
    break;

/******** Ped Red State ********/
    case Ped_Red_State:
    digitalWrite(Ped_Green ,LOW);
    digitalWrite(Ped_Red ,HIGH);
    Wire.beginTransmission(8); // transmit to device #9
    Wire.write(4); // sends current state value
    Wire.endTransmission();    // stop transmitting
    Current_State = Red_State;
    break;
  }//switch bracket
}//void loop braket
