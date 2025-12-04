// Arduino C code
const int STAR = 6;
const int DELTA = 7;
const int RUNLED = 5;
const int OVERLOAD = 13;

unsigned long t = 0;
bool proses = false;

void setup() {
  Serial.begin(115200);
  pinMode(STAR, OUTPUT);
  pinMode(DELTA, OUTPUT);
  pinMode(RUNLED, OUTPUT);
  pinMode(OVERLOAD, INPUT_PULLUP);

  digitalWrite(STAR, 0);
  digitalWrite(DELTA, 0);
  digitalWrite(RUNLED, 0);

  Serial.println("READY");
}

void loop() {
  if (digitalRead(OVERLOAD) == LOW) {
    digitalWrite(STAR,0);
    digitalWrite(DELTA,0);
    digitalWrite(RUNLED,0);
    proses = false;
    Serial.println("OVERLOAD");
    delay(300);
  }

  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd == "START") {
      digitalWrite(RUNLED,1);
      digitalWrite(STAR,1);
      digitalWrite(DELTA,0);
      t = millis();
      proses = true;
      Serial.println("STAR");
    }
    else if (cmd == "STOP") {
      digitalWrite(RUNLED,0);
      digitalWrite(STAR,0);
      digitalWrite(DELTA,0);
      proses = false;
      Serial.println("STOP");
    }
    else if (cmd == "RESET") {
      Serial.println("RESET_OK");
    }
  }

  if (proses && millis()-t >= 5000) {
    digitalWrite(STAR,0);
    digitalWrite(DELTA,1);
    proses = false;
    Serial.println("DELTA");
  }
}
