
int carred=11;
int caryellow=10;
int cargreen=9; 

void setup()
{
  pinMode(carred,OUTPUT);
  pinMode(cargreen,OUTPUT);
  pinMode(caryellow,OUTPUT);
  
  digitalWrite(carred,LOW);
  digitalWrite(caryellow,LOW);
  digitalWrite(cargreen,LOW);
}

void loop()
{
  digitalWrite(carred,LOW);
  digitalWrite(caryellow,HIGH);
  digitalWrite(cargreen,LOW);
  delay(2000);
  
  digitalWrite(carred,LOW);
  digitalWrite(caryellow,LOW);
  digitalWrite(cargreen,HIGH);
  delay(3000);
  
  digitalWrite(carred,LOW);
  digitalWrite(caryellow,HIGH);
  digitalWrite(cargreen,LOW);
  delay(2000);
  
  digitalWrite(carred,HIGH);
  digitalWrite(caryellow,LOW);
  digitalWrite(cargreen,LOW);
  delay(4000);
}