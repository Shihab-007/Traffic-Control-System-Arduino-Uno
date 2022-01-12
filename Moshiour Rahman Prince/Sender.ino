//Arduino A
#include <Wire.h>

#define red 7
#define yellow 6
#define green 5
#define pRed 10 
#define pGreen 9

int T_Delay= 1000;
int button_input= 2;
volatile int button_state= 0;
volatile bool Hub= true;
  
void setup()
{ 
  Wire.begin();
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
 
  if(Hub == true){
    First_Lane();
    delay(500);
   
    Wire.beginTransmission(1);
    Wire.write(Hub);
    Wire.endTransmission();
   }
 
    T_red();
    delay(2000);
 
    Wire.requestFrom(1,1);
    while(Wire.available()){
    Hub = Wire.read();
    Serial.println(Hub);}  
 
}






void First_Lane(){
  
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