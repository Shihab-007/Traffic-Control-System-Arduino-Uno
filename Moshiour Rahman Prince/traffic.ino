
int red=7;
int yellow=6;
int green=5;

void setup()
{
  pinMode(red,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green,OUTPUT);
  
  digitalWrite(red,LOW);
  digitalWrite(yellow,LOW);
  digitalWrite(green,LOW);
}

void loop()
{
  digitalWrite(red,LOW);
  digitalWrite(yellow,HIGH);
  digitalWrite(green,LOW);
  delay(2000);
  
  digitalWrite(red,LOW);
  digitalWrite(yellow,LOW);
  digitalWrite(green,HIGH);
  delay(3000);
  
  digitalWrite(red,LOW);
  digitalWrite(yellow,HIGH);
  digitalWrite(green,LOW);
  delay(2000);
  
  digitalWrite(red,HIGH);
  digitalWrite(yellow,LOW);
  digitalWrite(green,LOW);
  delay(4000);
}