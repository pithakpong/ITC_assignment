
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
pinMode(12,OUTPUT);
//digitalWrite(12,HIGH);
pinMode(11,OUTPUT);
//digitalWrite(11,LOW);
pinMode(10,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly: 
 pinMode(12,OUTPUT);
  pinMode(11,INPUT);
  pinMode(10,OUTPUT);
  digitalWrite(12,LOW); 
  digitalWrite(10,HIGH);
  delay(500);
  pinMode(12,OUTPUT);
  pinMode(11,INPUT);
  pinMode(10,OUTPUT);
  digitalWrite(12,HIGH); 
  digitalWrite(10,LOW);
  delay(500);
  pinMode(12,INPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  digitalWrite(11,LOW); 
  digitalWrite(10,HIGH);
  delay(500);
  pinMode(12,INPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  digitalWrite(11,HIGH); 
  digitalWrite(10,LOW);
  delay(500);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,INPUT);
  digitalWrite(12,LOW); 
  digitalWrite(11,HIGH);
  delay(500);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,INPUT);
  digitalWrite(12,HIGH); 
  digitalWrite(11,LOW);
  delay(500);
  //ขาย้อน
    pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,INPUT);
  digitalWrite(12,HIGH); 
  digitalWrite(11,LOW);
  delay(500);
    pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,INPUT);
  digitalWrite(12,LOW); 
  digitalWrite(11,HIGH);
  delay(500);
    pinMode(12,INPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  digitalWrite(11,HIGH); 
  digitalWrite(10,LOW);
  delay(500);
   pinMode(12,INPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  digitalWrite(11,LOW); 
  digitalWrite(10,HIGH);
  delay(500);
  pinMode(12,OUTPUT);
  pinMode(11,INPUT);
  pinMode(10,OUTPUT);
  digitalWrite(12,HIGH); 
  digitalWrite(10,LOW);
  delay(500);
   pinMode(12,OUTPUT);
  pinMode(11,INPUT);
  pinMode(10,OUTPUT);
  digitalWrite(12,LOW); 
  digitalWrite(10,HIGH);
  delay(500);
  

  
}

  
