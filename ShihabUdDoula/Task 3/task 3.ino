#define stateRed 0
#define stateYellow 1
#define stateGreen 2
#define crossing 100
#define notCrossing 111

int carred=11;
int caryellow=10;
int cargreen=9; 
int padred=13;
int padgreen=12;
int padpushbutton=2;

volatile int t20;
volatile bool change;

int pedState = crossing;
int state = stateRed;

void setup()
{
  pinMode(carred,OUTPUT);
  pinMode(cargreen,OUTPUT);
  pinMode(caryellow,OUTPUT);
  
  pinMode(padgreen,OUTPUT);
  pinMode(padred,OUTPUT);
  
  pinMode(padpushbutton,INPUT_PULLUP);
  pinMode(padred,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(padpushbutton),padControl,CHANGE);
  
}
void padControl()
{
  change = true;
  state= stateRed;
  
}

void loop()
{ 
  t20= 4500;
  if (change == true)
  {
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
      delay(4000);
      digitalWrite(caryellow, LOW);
      digitalWrite(cargreen, LOW);
    
      state = stateYellow;
    
    break;

 	case stateYellow:
    
      digitalWrite(carred, LOW);
      digitalWrite(caryellow, HIGH);
      delay(4000);
      digitalWrite(cargreen, LOW);
    
      state = stateGreen;
    break;
      
    case stateGreen:
    
      digitalWrite(carred, LOW);
      digitalWrite(caryellow, LOW);
      digitalWrite(cargreen, HIGH);
      delay(4000);
      digitalWrite(cargreen, LOW);
      digitalWrite(caryellow, HIGH);
	  delay(4000);
      digitalWrite(caryellow, LOW);

      state = stateRed;

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
          delay(t20);
          digitalWrite(padgreen,LOW);
          digitalWrite(padred,LOW);
      	
      	  state = notCrossing;
      	break;
      
      case notCrossing:
          digitalWrite(padred,HIGH);
          delay(t20);
          digitalWrite(padred,LOW);
          digitalWrite(padgreen,LOW);
      	
      	  state = crossing;
      	break;
      
      default:
      break;
    }


}