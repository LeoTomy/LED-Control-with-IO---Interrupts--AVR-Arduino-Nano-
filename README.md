## 🚦 LED Control with IO & Interrupts (AVR/Arduino Nano)

![License](https://img.shields.io/badge/license-MIT-green.svg)
![Top language](https://img.shields.io/github/languages/top/LeoTomy/LED-Control-with-IO---Interrupts--AVR-Arduino-Nano-)


## 📖 Overview
This project demonstrates **IO handling and interrupt-driven programming** on an AVR-based microcontroller (Arduino Nano).  
The system uses **three buttons and multiple LEDs** to create an intelligent light sequence, fully implemented on **register level** without Arduino libraries.

---

## 📌 Features
- **LED Running Light (Lauflicht)**:  
  - Starts when **Button S1** is pressed.  
  - LEDs blink in sequence with **500 ms pause**.  
  - Sequence repeats **3 times**, then waits for S1 again.

- **Speed Control (S2)**:  
  - Pressing **Button S2** reduces the pause time between LED steps from **500 ms → 200 ms**.

- **Interrupt Control (S3)**:  
  - Pressing **Button S3** triggers an **external interrupt**.  
  - This permanently **disables the two outer LEDs** in the light sequence.

---

## ⚙️ Hardware Requirements
| Component                 | Pin Connection            |
| ------------------------- | ------------------------- |
| LED1–LED3                 | PD5–PD7                   |
| LED4–LED8                 | PB0–PB4                   |
| Button S1                 | PD4                       |
| Button S2                 | PD3 (INT1)                |
| Button S3                 | PD2 (INT0)                |
| Resistors                 | Current limiting for LEDs |
| Breadboard & Jumper wires | -                         |
---

## 🖥️ Software Requirements
- **AVR-GCC** or **Arduino IDE** (for compiling & uploading)  
- No Arduino libraries used → direct **register-level programming**  

---

## 🚀 How to Run
1. Clone the repository:
   ```bash
   git clone https://github.com/LeoTomy/LED-Control-with-IO---Interrupts--AVR-Arduino-Nano-
2. Open the project in Arduino IDE or compile with AVR-GCC.
3. Upload to your Arduino Nano (ATmega328P).
4. Connect the circuit:
5. S1 → Start sequence
6. S2 → Speed change
7. S3 → Interrupt disable LEDs
8. Press S1 to start the LED sequence.

---

## 🎯 Learning Outcomes
Understanding digital IO with AVR registers

Implementing hardware interrupts

Designing a state-dependent LED control system

Programming without Arduino libraries → closer to real embedded development

---

## 🧭 Demo
https://youtu.be/YP0IIaIXWzg

---

## 📖 License
This project is licensed under the MIT License.
Feel free to use, modify, and share.

