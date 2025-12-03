# ArduPys Controller — Star Delta GUI

Simple **Star–Delta motor control simulation** using **Python Tkinter GUI** + **Arduino UNO** via Serial.

---

## 🔌 Hardware Setup

| Function         | Pin |
|-----------------|-----|
| RUN LED (Green)  | 5   |
| STAR LED (Yellow)| 6   |
| DELTA LED (Red)  | 7   |
| Overload Button  | 13  |

---

## 📡 Serial Commands

- `START`  
- `STOP`  
- `RESET`  
- `STATE:STAR`  
- `STATE:DELTA`  
- `OVERLOAD`  

---

## 🖥 Python GUI (`gui.py`)

```python
import tkinter as tk
import serial, threading, time

# Adjust COM port according to your PC
ser = serial.Serial("COM8", 115200, timeout=1)
time.sleep(2)

def send(x):
    ser.write((x+"\n").encode())

def update_status(text, color):
    lbl.config(text=text, bg=color)

def listen():
    while True:
        try:
            r = ser.readline().decode().strip()
            if not r: 
                continue
            print(">>", r)

            if r == "STAR": update_status("STAR", "yellow")
            elif r == "DELTA": update_status("DELTA", "green")
            elif r == "STOP": update_status("STOP", "grey")
            elif r == "OVERLOAD": update_status("OVERLOAD", "red")
            elif r == "RESET_OK": update_status("READY", "white")

        except Exception:
            pass

root = tk.Tk()
root.title("Star Delta")
root.geometry("300x230")

lbl = tk.Label(root, text="READY", font=("Arial",20), bg="white")
lbl.pack(pady=10)

tk.Button(root, text="START", font=("Arial",14),
          command=lambda: send("START"), width=12, bg="#4CAF50", fg="white").pack(pady=4)

tk.Button(root, text="STOP", font=("Arial",14),
          command=lambda: send("STOP"), width=12, bg="#F44336", fg="white").pack(pady=4)

tk.Button(root, text="RESET", font=("Arial",14),
          command=lambda: send("RESET"), width=12).pack(pady=4)

threading.Thread(target=listen, daemon=True).start()

root.mainloop()

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