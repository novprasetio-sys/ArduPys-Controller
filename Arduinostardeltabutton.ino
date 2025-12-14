const int onButton = 11;
const int offButton = 12;
const int overloadButton = 13;
const int runLed = 5;
const int starLed = 6;
const int deltaLed = 7;
unsigned long previousMillis = 0;
const long interval = 5000; // 5 detik
int motorState = 0; // 0: OFF, 1: STAR, 2: DELTA
void setup() {
pinMode(onButton, INPUT);
pinMode(offButton, INPUT);
pinMode(overloadButton, INPUT);
pinMode(runLed, OUTPUT);
pinMode(starLed, OUTPUT);
pinMode(deltaLed, OUTPUT);
}
void loop() {
if (digitalRead(offButton) == HIGH || digitalRead(overloadButton) == HIGH) 
{
motorState = 0;
digitalWrite(runLed, LOW);
digitalWrite(starLed, LOW);
digitalWrite(deltaLed, LOW);
}
if (digitalRead(onButton) == HIGH && motorState == 0) 
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

