#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#define Leftbutton 12
#define Rightbutton 11
#define Buzzer 8 
#define PlayerWidth 10 
char Vector_pong[4] ={'U','D','u','d'};// U is upright: D is upleft: u is downright: d is downleft
//char IndexStart;
char Index;
int Pos_pong[2]; 
int randomVector;
int Pos_player[2] = {60,31};
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

// varieble debouce
int lastButtonStateLeft = LOW;
int ButtonStateLeft = LOW; 
unsigned long long int lastTimeStateLeft; 
int lastButtonStateRight = LOW; 
int ButtonStateRight = LOW; 
unsigned long long int lastTimeStateRight; 

//varieble control player 
unsigned long long int coolDownLeft = 0; 
unsigned long long int coolDownRight = 0; 
int LeftState; 
int RightState;
void Displayplayer() 
{ 
  u8g2.clearBuffer();
  for(int i=0;i<PlayerWidth;i++) 
{ 
  u8g2.drawPixel(Pos_player[0]+i,Pos_player[1]);
}  
u8g2.sendBuffer();
}
void ControlLeft() 
{ 
  if(ButtonStateLeft) 
  {  
    if(Pos_player[0] >=1)
        Pos_player[0]-= 2;
  }
} 
void ControlRight() 
{ 
  if(ButtonStateRight) 
  {  
    if(Pos_player[0] < 119)
      Pos_player[0]+= 2;
  }
}
void Player_control() 
{ 
  ControlLeft(); 
  ControlRight();
}
void Upright() 
{  

     if(Pos_pong[0] < 127 && Pos_pong[1] > 0) 
    { 
    u8g2.clearBuffer();
    u8g2.drawPixel(Pos_pong[0]++,Pos_pong[1]--);
    u8g2.sendBuffer();
    } 

}
void Upleft() 
{ 
 
    if(Pos_pong[0] > 0 && Pos_pong[1] > 0) 
  { 
    u8g2.clearBuffer();
    u8g2.drawPixel(Pos_pong[0]--,Pos_pong[1]--);
    u8g2.sendBuffer();
  }

}
void Downright() 
{  

   if(Pos_pong[0] < 127 && Pos_pong[1] < 31) 
  { 
    u8g2.clearBuffer();
    u8g2.drawPixel(Pos_pong[0]++,Pos_pong[1]++);
    u8g2.sendBuffer();
  } 
  
}
void Downleft() 
{  

   if(Pos_pong[0] > 0 && Pos_pong[1] < 31) 
  { 
    u8g2.clearBuffer();
    u8g2.drawPixel(Pos_pong[0]--,Pos_pong[1]++);
    u8g2.sendBuffer();
  } 
  
}
void Screen() 
{ 
  for(int i=0;i<=127;i++) 
    u8g2.drawPixel(i,0);
  for(int j=0;j<=31;j++) 
    { 
      u8g2.drawPixel(0,j); 
      u8g2.drawPixel(127,j);
    }
    u8g2.sendBuffer();
}
void DisplayPong() 
{ 
  Screen();
  if(Index == 'U') 
    Upright();
  else if(Index == 'D') 
    Upleft(); 
  else if(Index == 'd') 
    Downleft();
  else if(Index == 'u') 
    Downright();
}

void debouceLeft() 
{ 
  int ReadingLeft = digitalRead(Leftbutton); 
  if(ReadingLeft != lastButtonStateLeft) 
    lastTimeStateLeft = millis();
  if(millis() - lastTimeStateLeft > 50) 
    ButtonStateLeft = ReadingLeft; 
  lastButtonStateLeft = ReadingLeft; 
  
} 
void debouceRight() 
{ 
  int ReadingRight = digitalRead(Rightbutton);  
  if(ReadingRight != lastButtonStateRight) 
    lastTimeStateRight = millis(); 
  if(millis() - lastTimeStateRight > 50) 
    ButtonStateRight = ReadingRight;
  lastButtonStateRight = ReadingRight;
}
void ReflectVector() 
{ 

  if((Index == 'U') && (Pos_pong[0] == 127 || Pos_pong[1] == 0)) 
  { 
    if(Pos_pong[0] == 127)  
      { 
    Index = 'D';
      }
     else if(Pos_pong[1] == 0) 
     { 
    Index = 'u';
     }
  }
    
  else if((Index == 'D') && (Pos_pong[0] == 0 || Pos_pong[1] == 0))  
  { 
    if(Pos_pong[0] == 0 )  
    { 
    Index = 'U';
    } 
    else if(Pos_pong[1] == 0) 
    { 
    Index = 'd';
    }
  }
    
  else if((Index == 'd') && (Pos_pong[0] == 0 || Pos_pong[1] == 31))  
  { 
    if(Pos_pong[0] == 0 ) 
    { 
    Index = 'u';
    }
    else 
    { 
      if(Pos_pong[1] == 31) 
      { 
        if(Pos_pong[0] >= Pos_player[0] && Pos_player[0] + 9 >= Pos_pong[0]) 
        { 
          tone(Buzzer,262); 
          delay(50);
          noTone(Buzzer);
          Index = 'D';
        }
      }
      else 
        { 
          Pos_pong[0] = -1;
          Pos_pong[0] = -1;
        } 
    }

  }
    
  else if((Index == 'u') && (Pos_pong[0] == 127 || Pos_pong[1] == 31))  
  { 
    if(Pos_pong[0] == 127) 
    { 
    Index = 'd';
    }
    else 
    { 
       if(Pos_pong[1] == 31) 
      { 
         if(Pos_pong[0] >= Pos_player[0] && Pos_player[0] + 9 >= Pos_pong[0]) 
        {
          tone(Buzzer,262); 
          delay(50);
          noTone(Buzzer); 
          Index = 'U';
        } 
        else 
        { 
          Pos_pong[0] = -1;
          Pos_pong[0] = -1;
        }
      }
    }

  } 
}
void setup(void) { 
  Serial.begin(9600);
   u8g2.begin();
   pinMode(Leftbutton,INPUT); 
   pinMode(Rightbutton,INPUT); 
   pinMode(Buzzer,OUTPUT);
   randomSeed(analogRead(A0)); 
   Pos_pong[0] = random(0,127);
   Pos_pong[1] = random(10,20);
   randomVector = random(0,3);
   Index = Vector_pong[randomVector];
}
// U is upright: D is upleft: u is downright: d is downleft
void loop(void) {
  debouceLeft();
  debouceRight();
Screen(); 
Displayplayer();
Player_control();
ReflectVector(); 
DisplayPong();
Serial.print(ButtonStateLeft); 
Serial.print(" "); 
Serial.println(ButtonStateRight); 
}
