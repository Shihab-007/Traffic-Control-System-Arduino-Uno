//Arduino B
#include <Wire.h>

#define red 7
#define yellow 6
#define green 5
#define pRed 10 
#define pGreen 9

int T_Delay= 1000;
int button_input= 2;
volatile int button_state= 0;
volatile bool Hub;

void setup()
{ 
  Wire.begin(1);                
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(9600);
  
  pinMode(red,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green,OUTPUT);
  
  pinMode(pRed,OUTPUT);
  pinMode(pGreen,OUTPUT);
  pinMode(button_input,INPUT);
  
  digitalWrite(pRed,HIGH);
  
  attachInterrupt(digitalPinToInterrupt(button_input),Interruption,CHANGE);
 
}


void loop(){

   T_red();
   delay(500); 
  
  if(Hub == true){
    Second_Lane();
    delay(100);
    
    Hub= false;  
  }
  
}

void Second_Lane(){
  
 if (button_state == 1){
 Pedastrian_lane ();
 
  }else{    
  Traffic_lane ();
  }

}

void Pedastrian_lane (){
    P_green();
    delay(2000);
    P_Red();
    delay(1000);
    button_state=0;  
} 

void Traffic_lane ()
{
  T_yellow ();
  delay(T_Delay);
  
  T_green ();
  delay(T_Delay);
  
  T_yellow ();
  delay(T_Delay);
  
  T_red();
  delay(T_Delay);
   
}

void T_red(){  
  digitalWrite(red,HIGH);
  digitalWrite(yellow,LOW);
  digitalWrite(green,LOW); 
}

void T_yellow (){
  digitalWrite(red,LOW);
  digitalWrite(yellow,HIGH);
  digitalWrite(green,LOW);
}

void T_green (){  
  digitalWrite(red,LOW);
  digitalWrite(yellow,LOW);
  digitalWrite(green,HIGH);
}


void P_green() {  
 digitalWrite(pRed,LOW);
 delay(500);
 digitalWrite(pGreen,HIGH); 
}

void P_Red() {
 digitalWrite(pGreen,LOW);
 delay(300);
 digitalWrite(pRed,HIGH);  
}

void Interruption(){
  button_state= 1;
}

void receiveEvent(int howMany)
  {
  while(Wire.available()) 
  {
    Hub = Wire.read(); 
    Serial.println(Hub);
  }}

void requestEvent()
{
    Wire.write(Hub =! Hub);
    Serial.println(Hub);
}
