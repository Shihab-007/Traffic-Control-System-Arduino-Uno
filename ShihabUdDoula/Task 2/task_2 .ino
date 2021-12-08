#define stateRed 0
#define stateYellow 1
#define stateGreen 2

int carred=11;
int caryellow=10;
int cargreen=9; 
int padred=13;
int padgreen=12;
int padpushbutton=2;

volatile bool change;

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
  //stateMachine();
 if (change == true)
  {
    state= stateRed;
    stateMachine();
    digitalWrite(padgreen,HIGH);
    delay(4500);
    digitalWrite(padred,LOW);
    digitalWrite(padgreen,HIGH);
    
    change = false;
  }
  else
  {
  	if(state == stateGreen || state == stateYellow)
    {
     	stateMachine();
      	digitalWrite(padgreen, LOW);
        digitalWrite(padred, HIGH);
        delay(4500);
        digitalWrite(padred, LOW);
    }
    else 
    {
    	stateMachine();
      	digitalWrite(padgreen, HIGH);
        delay(4500);  
        digitalWrite(padgreen, LOW);
        digitalWrite(padred, LOW);
    }
  }
}

void stateMachine()
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
      
      
  }
}
