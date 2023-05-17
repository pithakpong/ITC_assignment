int led[3] = {4,3,2};
unsigned long long int cooldown[3];
long int ledStartTime[3] = {0,-2000, 0}; //-2000 คือ ทำให้เงื่อนไขของการกระพริบเหลือเป็นเท็จตอนอัพโหลด 
bool ledState[3] = {LOW, LOW, LOW};
void toggleLED(int i)                         
    {                                           
        if (millis() - cooldown[i] > 50) 
        {                                       
            ledStartTime[i] = millis();         
            ledState[i] = !ledState[i];         
            digitalWrite(led[i], ledState[i]);       
        }                                       
        cooldown[i] = millis();                 
    }
int button[3] = {12, 11, 10}; 

bool buttonState[3] = {LOW, HIGH, HIGH};
bool reading[3];
bool lastButtonState[3] = {LOW, HIGH, HIGH};
unsigned long long int lastDebounceTime[3];
bool yellow = LOW;
void debounce(int i)
{
    reading[i] = digitalRead(button[i]);
    if (reading[i] != lastButtonState[i])
        lastDebounceTime[i] = millis();

    if (millis() - lastDebounceTime[i] > 50)
    {
        buttonState[i] = reading[i];
    }
    lastButtonState[i] = reading[i];
}
void setup()
{
    Serial.begin(9600);
    pinMode(led[0], OUTPUT);
    pinMode(led[1], OUTPUT);
    pinMode(led[2], OUTPUT);
    pinMode(button[0], INPUT);        //PULLDOWN
    pinMode(button[1], INPUT);        //PULLUP
    pinMode(button[2], INPUT_PULLUP); //PULLUPBUILTIN
}
void loop()
{
    debounce(0); // b1 RED
    if (!ledState[0])
    {
        debounce(2); // b3 GREEN
        if (!ledState[2])
            debounce(1); // b2 YELLOW
    }
    if (millis() - ledStartTime[0] > 3000) // RED
    {
        ledState[0] = LOW;
        digitalWrite(led[0], ledState[0]);
    }
    if (millis() - ledStartTime[2] > 3000) //GREEN
    {
        ledState[2] = LOW;
        digitalWrite(led[2], ledState[2]);
    }
    if (millis() - ledStartTime[1] > 2000) // YELLOW
    {
        ledState[1] = LOW;
        digitalWrite(led[1], ledState[1]);
    }
    else
    {
        if (millis() - ledStartTime[1] < 500)
        {
            ledState[1] = HIGH;
            digitalWrite(led[1], ledState[1]);
        }
        else if (millis() - ledStartTime[1] < 1000)
        {
            ledState[1] = LOW;
            digitalWrite(led[1], ledState[1]);
        }
        else if (millis() - ledStartTime[1] < 1500)
        {
            ledState[1] = HIGH;
            digitalWrite(led[1], ledState[1]);
        }
    }
    //Setting LED
    if (buttonState[0])
        toggleLED(0);
    if (!buttonState[1])
        toggleLED(1); 
    if (!buttonState[2])
        toggleLED(2);
}
