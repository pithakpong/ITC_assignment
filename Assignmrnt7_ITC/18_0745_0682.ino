//test oled  
#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32   
#define buzzer 6
#define button_alarm 5
#define Input_Slide A1
#define MH_sensor A0
#define led1 11 
#define led2 10 
#define led3 9 
#define led4 8  
#define button 12
#define led_alarm 4 
unsigned long long int LastTime = 1000;
byte hour; 
byte minute;  
byte hour_alarm; 
byte minute_alarm; 
byte second_alarm;
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); 
int lock = 0; 
int second = 1; 
int StateLed1 = 0;
int StateLed2 = 0;
int StateLed3 = 0;
int StateLed4 = 0; 
int count = 0; 
int Timesong = 0; 
bool Onsong = false; 
unsigned long long int lastTimeState;  
bool lastState = false; 
bool buttonState = false;
unsigned long long int lastTimeState_alarm;  
bool lastState_alarm = false; 
bool buttonState_alarm = false;
unsigned long long int cooldown = 0; 
unsigned long long int cooldown_alarm = 0; 
bool toggleAlarm = false;
void debouce() 
{ 
  bool reading = digitalRead(button);
  if(reading != lastState)
    lastTimeState = millis();
  if(millis() - lastTimeState >= 50) 
    buttonState = reading;
  lastState = reading;
}

void debouce_alarm() 
{ 
  bool reading = digitalRead(button_alarm);
  if(reading != lastState_alarm)
    lastTimeState = millis();
  if(millis() - lastTimeState >= 50) 
    buttonState_alarm = reading;
  lastState_alarm = reading;
}
void setup() { 
Serial.begin(9600);
pinMode(led1,OUTPUT); 
pinMode(led2,OUTPUT); 
pinMode(led3,OUTPUT);
pinMode(led4,OUTPUT); 
pinMode(button,INPUT); 
pinMode(buzzer,OUTPUT); 
pinMode(button_alarm,OUTPUT);
pinMode(led_alarm,OUTPUT);
hour = EEPROM.read(0); 
minute = EEPROM.read(1); 
second =EEPROM.read(2);
hour_alarm = EEPROM.read(60);
minute_alarm = EEPROM.read(61);
second_alarm = EEPROM.read(62);
if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  
}
void loop() {  
int slide_value = analogRead(Input_Slide); 
int casting_slide = map(slide_value,0,1023,0,60); 
int casting_hour = map(slide_value,0,1203,0,24);
debouce(); 
debouce_alarm(); 
Serial.println(buttonState_alarm); 
if(buttonState_alarm && !lastState_alarm) 
{ 
  if(millis() - cooldown_alarm >= 150) 
  { 
     //Serial.print("  Yes");
     toggleAlarm = true;
     cooldown_alarm = millis();
  }
    
}
if(buttonState && !lastState) 
{ 
  if(toggleAlarm) 
  { 
    tone(buzzer,252);
    delay(50);
    noTone(buzzer);
  }
  if(millis() - cooldown >= 150)  
  { 
    count++;
    cooldown = millis();
  }
}
if(hour == hour_alarm && minute == minute_alarm && second == second_alarm) 
  Onsong = true;
if(Onsong) 
{ 
  if(Timesong<=15)  
  { 
    tone(buzzer,252);
    delay(50);
    noTone(buzzer);
  }
  else 
    Onsong = false;
    
     
}
if(count > 4)  
 count = 0; 
if(count >=1 && count <=4 && toggleAlarm == false) 
{   
 lock = 1;
if(count == 1) 
{ 
  StateLed1 = 1; 
  hour = map(slide_value,0,1023,0,24);
}
  
if(count == 2)  
{ 
  StateLed1 = 0;
  StateLed2 = 1;
  minute = casting_slide;
}
  
if(count == 3)  
{ 
  StateLed2 = 0;
  StateLed3 = 1;
  second = casting_slide;
}
  
if(count == 4) 
{ 
  StateLed3 = 0;
  StateLed4 = 1;
}
  
} 
//Serial.print(hour_alarm); 
//Serial.print(" : "); 
//Serial.print(minute_alarm); 
//Serial.print(" : "); 
//Serial.print(second_alarm); 
//Serial.print(" : "); 
//Serial.print(count);
//Serial.print(" : "); 
//Serial.println(toggleAlarm);
if(digitalRead(MH_sensor)) {
  oled.dim(0); 
}
else {
  oled.dim(1);
}
digitalWrite(led1,StateLed1);
digitalWrite(led2,StateLed2);
digitalWrite(led3,StateLed3);
digitalWrite(led4,StateLed4); 
digitalWrite(led_alarm,toggleAlarm);
if(lock == 1 && count == 4 && toggleAlarm == false) 
{ 
  EEPROM.update(0,hour);
  EEPROM.update(1,minute);
  EEPROM.update(2,second); 
  lock = 0;
} 
if(toggleAlarm == true)  
{
  oled.clearDisplay(); // clear display
  oled.setTextSize(2);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 10);        // position to display
  oled.print(hour_alarm); // text to display
  oled.setCursor(20,10);        // position to display
  oled.print(" : "); // text to display
  oled.setCursor(50, 10);        // position to display
  oled.print(minute_alarm); // text to display
  oled.setCursor(70,10);        // position to display
  oled.print(" : "); // text to display
  oled.setCursor(100,10);        // position to display
  oled.print(second_alarm); // text to display
  oled.display();               // show on OLED  
  if(count == 1) 
{ 
  StateLed1 = 1; 
  hour_alarm = map(slide_value,0,1023,0,24);
}
  
if(count == 2)  
{ 
  StateLed1 = 0;
  StateLed2 = 1;
  minute_alarm = casting_slide;
}
  
if(count == 3)  
{ 
  StateLed2 = 0;
  StateLed3 = 1;
  second_alarm = casting_slide;
}
  
if(count == 4) 
{ 
  StateLed3 = 0;
  StateLed4 = 1; 
  EEPROM.update(60,hour_alarm); 
  EEPROM.update(61,minute_alarm);
  EEPROM.update(62,second_alarm); 
  count = 0;
  toggleAlarm = false;
}  
}
if(toggleAlarm == false) 
{ 
  oled.clearDisplay(); // clear display
  oled.setTextSize(2);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 10);        // position to display
  oled.print(hour); // text to display
  oled.setCursor(20,10);        // position to display
  oled.print(" : "); // text to display
  oled.setCursor(50, 10);        // position to display
  oled.print(minute); // text to display
  oled.setCursor(70,10);        // position to display
  oled.print(" : "); // text to display
  oled.setCursor(100,10);        // position to display
  oled.print(second); // text to display
  oled.display();               // show on OLED
} 
  
  if(count == 0 && toggleAlarm == false) 
  { 
  StateLed1 = 0;
  StateLed2 = 0;
  StateLed3 = 0;
  StateLed4 = 0; 
    lock = 0;

    if(millis() - LastTime > 1000)  
  { 
    if(Onsong) 
      Timesong++; 
    else 
      Timesong = 0;
    second++; 
    LastTime = millis();
    EEPROM.update(2,second);
  }
    

  if(second >= 60) 
  { 
    minute++; 
    second = 0;
    EEPROM.update(0,hour); 
    EEPROM.update(1,minute); 
    
 
  } 
  if(minute == 60) 
  { 
    hour++;
    minute = 0;
  }
  if(hour >= 24) 
    hour = 0; 
  }
}
