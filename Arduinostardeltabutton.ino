const int onButton = 13;
const int offButton = 12;
const int overloadButton = 11;
const int runLed = 2;
const int starLed = 3;
const int deltaLed = 4;
unsigned long previousMillis = 0;
const long interval = 5000; // 5 detik
int motorState = 0; // 0: OFF, 1: STAR, 2: DELTA
void setup() {
pinMode(onButton, INPUT_PULLUP);
pinMode(offButton, INPUT_PULLUP);
pinMode(overloadButton, INPUT_PULLUP);
pinMode(runLed, OUTPUT);
pinMode(starLed, OUTPUT);
pinMode(deltaLed, OUTPUT);
}
void loop() {
if (digitalRead(offButton) == LOW || digitalRead(overloadButton) == LOW) 
{
motorState = 0;
digitalWrite(runLed, LOW);
digitalWrite(starLed, LOW);
digitalWrite(deltaLed, LOW);
}
if (digitalRead(onButton) == LOW && motorState == 0) 
{
motorState = 1;
digitalWrite(runLed, HIGH);
digitalWrite(starLed, HIGH);
previousMillis = millis();
}
if (motorState == 1 && millis() - previousMillis >= interval) 
{
motorState = 2;
digitalWrite(starLed, LOW);
digitalWrite(deltaLed, HIGH);
}
delay(100);
}

