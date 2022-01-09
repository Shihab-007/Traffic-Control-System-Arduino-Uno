#define stateRed 0
#define stateYellow 1
#define stateGreen 2
#define crossing 100
#define notCrossing 111
#define flag1 3
#define flag2 4

#define carred 11
#define caryellow 10
#define cargreen 9
#define padred 13
#define padgreen 12
#define padpushbutton 2

volatile bool change;
volatile int flag;

int pedState = notCrossing;
int state = stateRed;

void setup()
{
  Serial.begin(9600);
  pinMode(carred,OUTPUT);
  pinMode(cargreen,OUTPUT);
  pinMode(caryellow,OUTPUT);
  
  pinMode(padgreen,OUTPUT);
  pinMode(padred,OUTPUT);
  
  pinMode(padpushbutton,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(padpushbutton),padControl,CHANGE);
  
}
void padControl()
{
  change = true;
  state= stateRed;
   pedState = crossing;
}

void loop()
{ 
  if (change == true)
  {
    pedState = crossing;
    stateMachinePed();
    stateMachineCar();
    
    change = false;
    
  }
  else
  {
  	pedState = notCrossing;
    stateMachinePed();
    state = stateGreen;
    stateMachineCar();
  }
}

void stateMachineCar()
{
  switch (state){

    case stateRed:
    
      digitalWrite(carred, HIGH);
      delay(2000);
      digitalWrite(caryellow, LOW);
      digitalWrite(cargreen, LOW);
      digitalWrite(carred, LOW);

      state = stateYellow;
      Serial.write(flag2);
    
    break;

 	case stateYellow:
    
      digitalWrite(carred, LOW);
      digitalWrite(caryellow, HIGH);
      delay(2000);
      digitalWrite(cargreen, LOW);
      digitalWrite(caryellow, LOW);

      state = stateGreen;
          Serial.write(flag2);

    break;
      
    case stateGreen:
    
      digitalWrite(carred, LOW);
      digitalWrite(caryellow, LOW);
      digitalWrite(cargreen, HIGH);
      delay(2000);
      digitalWrite(cargreen, LOW);
      digitalWrite(caryellow, HIGH);
	  delay(2000);
      digitalWrite(caryellow, LOW);

      state = stateRed;
          
    Serial.write(flag1);


    break;
    
    default:
    break;
      
  }
}
void stateMachinePed()
{
	switch(pedState)
    {
    	case crossing:
          digitalWrite(padgreen,HIGH);
          delay(2000);
          digitalWrite(padgreen,LOW);
          digitalWrite(padred,LOW);
      	
      	  state = notCrossing;
      	break;
      
      case notCrossing:
          digitalWrite(padred,HIGH);
          delay(2000);
          digitalWrite(padred,LOW);
          digitalWrite(padgreen,LOW);
      	
      	  state = crossing;
      	break;
      
      default:
      break;
    }


}
