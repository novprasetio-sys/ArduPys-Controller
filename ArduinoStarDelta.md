# Arduino Star–Delta Motor Control (Basic Simulation)

Project ini adalah simulasi **kontrol motor Star–Delta** menggunakan Arduino dengan input tombol dan output LED. Cocok untuk pembelajaran logika kontrol motor, sequencing, dan dasar interlock seperti pada panel motor industri.

---

## 📌 Deskripsi Singkat

Urutan kerja sistem:

1. Motor **OFF**
2. Tombol **ON ditekan** → Motor masuk mode **STAR**
3. Setelah **5 detik** → Otomatis pindah ke mode **DELTA**
4. Tombol **OFF** atau **OVERLOAD** ditekan → Motor **STOP** dan reset

Project ini hanya simulasi logika (LED), **bukan penggerak motor langsung**.

---

## 🔧 Hardware yang Digunakan

- Arduino Uno / Nano / kompatibel
- Push Button (3 buah)
  - ON
  - OFF
  - OVERLOAD
- LED (3 buah)
  - RUN
  - STAR
  - DELTA
- Resistor LED (220Ω – 330Ω)

---

## 🔌 Konfigurasi Pin

| Fungsi | Pin Arduino |
|------|------------|
| Tombol ON  | D13 |
| Tombol OFF | D12 |
| Tombol OVERLOAD | D11 |
| LED RUN | D2 |
| LED STAR | D3 |
| LED DELTA | D4 |

---

## ⚙️ Konsep State Motor

0 = OFF 1 = STAR 2 = DELTA
---

## 🧠 Cara Kerja Logika

- **ON ditekan**
  - Motor masuk state STAR
  - LED RUN dan STAR menyala
  - Timer dimulai menggunakan `millis()`

- **Setelah 5 detik**
  - Motor berpindah ke state DELTA
  - LED STAR mati
  - LED DELTA menyala

- **OFF / OVERLOAD ditekan**
  - Motor berhenti
  - Semua LED mati
  - State kembali ke OFF

---

## 💻 Source Code

```cpp
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
  pinMode(onButton, INPUT);
  pinMode(offButton, INPUT);
  pinMode(overloadButton, INPUT);

  pinMode(runLed, OUTPUT);
  pinMode(starLed, OUTPUT);
  pinMode(deltaLed, OUTPUT);
}

void loop() {

  if (digitalRead(offButton) == HIGH || digitalRead(overloadButton) == HIGH) {
    motorState = 0;
    digitalWrite(runLed, LOW);
    digitalWrite(starLed, LOW);
    digitalWrite(deltaLed, LOW);
  }

  if (digitalRead(onButton) == HIGH && motorState == 0) {
    motorState = 1;
    digitalWrite(runLed, HIGH);
    digitalWrite(starLed, HIGH);
    previousMillis = millis();
  }

  if (motorState == 1 && millis() - previousMillis >= interval) {
    motorState = 2;
    digitalWrite(starLed, LOW);
    digitalWrite(deltaLed, HIGH);
  }

  delay(100);
}