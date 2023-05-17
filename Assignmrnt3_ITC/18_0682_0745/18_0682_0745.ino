int number; // number to display
int buttonClick = 13;
int buttonCheck = 12;
int readingClick = LOW; 
int readingCheck = LOW; 
unsigned long long int lastTimeClick; 
unsigned long long int lastTimeCheck;
int lastStateClick = LOW;
int lastStateCheck = LOW; 
int buttonStateClick ; 
int buttonStateCheck ;
int SetInPattern = 1;
int SetInCheck;
boolean bitCheckIn;
int bitInNum;
int randomBefore = 0;
int Tran;
int bitPattern[10] = { 
  B10111111,//0
  B00001110,//1
  B01111011,//2
  B01011111,//3
  B11001110,//4
  B11011101,//5
  B11111101,//6
  B00001111,//7
  B11111111,//8
  B11011111//9
};
int bitCheck[3] = { 
  B10110111,// 0
  B10110101,// G
  B10110000 // L
};
unsigned long long int coolDown;
int randomNo;
const byte numPins = 8;
const int segmentPins[8] = {2,3,4,5,6,7,8,9};

//debounce button click
void DebounceClick()
{
  readingClick = digitalRead(buttonClick);
  if(lastStateClick != readingClick) 
  { 
    lastTimeClick = millis();
  } 
   if(millis() - lastTimeClick > 50) 
  { 
    buttonStateClick = readingClick;
  } 
  
  lastStateClick = readingClick;
  
}
//debounce Check
void DebounceCheck()
{
  readingCheck = digitalRead(buttonCheck);
  if(lastStateCheck != readingCheck)
  {
    lastTimeCheck = millis();
  } 
    if(millis() - lastTimeCheck > 50) 
    { 
      buttonStateCheck = readingCheck;
    }
  lastStateCheck = readingCheck; 
}

void StepNumber() 
{
  
  if(millis() - coolDown > 50) 
  { 
    if(SetInPattern == 10) 
    { 
      SetInPattern = 1;
    }
    for(int segment = 0;segment<8;segment++)
    { 
     bitInNum = bitRead(bitPattern[SetInPattern],segment);
     digitalWrite(segmentPins[segment],!bitInNum); 
    }   
    SetInPattern +=1;
    if(SetInPattern-1 ==  randomNo) 
    {
      randomBefore =  SetInPattern - 1;
      randomNo = random(1,10);   
    }
    

  }
   coolDown = millis(); 
}
void CheckNumber() 
{ 
  int match = SetInPattern -1;
  
  if(match == randomBefore) 
  { 
    for(int segment=0;segment<8;segment++) 
     { 
        bitCheckIn = bitRead(bitCheck[0],segment);
        digitalWrite(segmentPins[segment],!bitCheckIn);
     }
  }
     
  
  else if(match < randomNo) 
  { 
    for(int segment=0;segment<8;segment++) 
    { 
      bitCheckIn = bitRead(bitCheck[2],segment);
      digitalWrite(segmentPins[segment],!bitCheckIn);
    }
  }

  
   else if(match > randomNo) 
  { 
      for(int segment=0;segment<8;segment++) 
      { 
        bitCheckIn = bitRead(bitCheck[1],segment);
        digitalWrite(segmentPins[segment],!bitCheckIn);
      } 
  }
 
}


void setup () {
Serial.begin(9600);
for (int i = 0; i < numPins; i++) 
{ 
  pinMode(segmentPins[i], OUTPUT);  
}
pinMode(buttonClick,INPUT); 
pinMode(buttonCheck,INPUT);
randomSeed(analogRead(A0));
randomNo = random(1,10);
}
void loop()
{ 

DebounceClick();
DebounceCheck();
if(buttonStateClick) 
{ 
  StepNumber();
}
if(buttonStateCheck)
{ 
 CheckNumber();  
}
Serial.println(randomNo);

}
