#include <Arduino_FreeRTOS.h>
#include <queue.h>

#define BT1 11
#define BT2 12
#define BT3 13
#define LED1 5
#define LED2 6
#define LED3 7

// Copy for task pvParameters reference
const uint16_t Button1 = BT1;
const uint16_t Button2 = BT2;
const uint16_t Button3 = BT3;

QueueHandle_t Queue1;
QueueHandle_t Queue2;
QueueHandle_t Queue3;

void setup() {
  Serial.begin(9600);
  // Create queues of size 5
  Queue1 =  xQueueCreate(5, sizeof(int16_t));
  Queue2 =  xQueueCreate(5, sizeof(int16_t));
  Queue3 =  xQueueCreate(5, sizeof(int16_t));
  // Tasks for buttons
  xTaskCreate(ButtonTask, "Button 1 Task", 100, (void*) &Button1, 1, NULL);
  xTaskCreate(ButtonTask, "Button 2 Task", 100, (void*) &Button2, 1, NULL);
  xTaskCreate(ButtonTask, "Button 3 Task", 100, (void*) &Button3, 1, NULL);
  // Tasks for leds
  xTaskCreate(Led1_Task, "LED1 Task", 100, NULL, 1, NULL);
  xTaskCreate(Led2_Task, "LED2 Task", 100, NULL, 1, NULL);
  xTaskCreate(Led3_Task, "LED3 Task", 100, NULL, 1, NULL);
}

void ButtonTask(void* pvParameters) {
  const TickType_t xTicksToWait = pdMS_TO_TICKS(10);
  uint16_t* thisButton = (uint16_t*) pvParameters;
  int16_t valueToSend = 0;
  int16_t lastPush = LOW;
  uint32_t timeNow = 0;
  uint32_t lastTime = 0;
  uint32_t timeDebounce = 200;

  // Queue for this button
  QueueHandle_t thisQueue;
  if (*thisButton == BT1) {
    thisQueue = Queue1;
  }
  else if (*thisButton == BT2) {
    thisQueue = Queue2;
  }
  else if (*thisButton == BT3) {
    thisQueue = Queue3;
  }

  pinMode(*thisButton, INPUT);

  while(1) 
  { 
    // Send LOW if not push
    valueToSend = LOW;

    timeNow = millis();
    if (timeNow - lastTime > timeDebounce) {
      int16_t readValue = digitalRead(*thisButton);
      // Send HIGH on first push
      if (readValue == HIGH && lastPush == LOW) {
        valueToSend = HIGH;
        lastTime = timeNow;
      }
      // Update last push
      if (readValue != lastPush) {
        lastPush = readValue;
      }
    }
    xQueueSend(thisQueue, &valueToSend, xTicksToWait);
    vTaskDelay(10);
  }
}
  
void Led1_Task(void* pvParameters) {
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  int16_t valueReceived = 0;
  bool Work = false; 
  bool receive = true;
  unsigned long long int Time;
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, LOW);
  while(1)
  {
    // Get button push
    if (xQueueReceive(Queue1, &valueReceived, xTicksToWait) == pdPASS) {
      if (valueReceived == HIGH) { 
        if(receive) 
        { 
           Work = true;
           receive = false;
           Time = millis();
        }
          
      } 
      if(Work && !receive) 
      { 
        if(millis() - Time >= 0 && millis() - Time < 500) 
          digitalWrite(LED1,HIGH);
        if(millis() - Time >= 500 && millis() - Time < 1000)
          digitalWrite(LED1,LOW); 
        if(millis() - Time >= 1000 && millis() - Time < 1500)
          digitalWrite(LED1,HIGH);
        if(millis() - Time >= 1500 && millis() - Time < 2000)
          digitalWrite(LED1,LOW); 
        if(millis() - Time >= 2000 && millis() - Time < 2500)
          digitalWrite(LED1,HIGH); 
        if(millis() - Time >= 2500 && millis() - Time < 3000) 
        { 
          digitalWrite(LED1,LOW); 
          receive = true;
        }
          
      }
    }
  } 
}

void Led2_Task(void* pvParameters) {
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  int16_t valueReceived = 0;
  bool toggleState = false;
  bool rappingLED = false;
  unsigned long long int Time = 0;
  pinMode(LED2, OUTPUT);
  digitalWrite(LED2, LOW);
  while(1)
  {
    // Get button push 
    if (xQueueReceive(Queue2, &valueReceived, xTicksToWait) == pdPASS) {
      if (valueReceived == HIGH) {
        toggleState = !toggleState;  
      if(toggleState) 
          Time = millis();      
      }
        
      if(millis() - Time > 200) 
      { 
        rappingLED = !rappingLED;  
        Time = millis();
      } 
      if(toggleState)
         digitalWrite(LED2,rappingLED); 
      else 
         digitalWrite(LED2,LOW);
    } 
  }
}

void Led3_Task(void* pvParameters) {
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  int16_t valueReceived = 0;
  int input = 0;
  int Chase = 0;
  unsigned long long int Time;
  pinMode(LED3, OUTPUT);
  digitalWrite(LED3, LOW);

  while(1)
  { 
    // Get button push
    if (xQueueReceive(Queue3, &valueReceived, xTicksToWait) == pdPASS) {
      if (valueReceived == HIGH ) {
        input++;
        
      } 
      if(input == Chase)
          Time = millis();
      if(millis() - Time >= 3000 && Chase < input ) 
      { 
        Chase++;
        Time = millis();
      }
      if(input>Chase) 
        digitalWrite(LED3,HIGH);
      else 
      { 
        digitalWrite(LED3,LOW);
        input = 0;
        Chase = 0;
      }
        
    }
  }
}

void loop() {}
