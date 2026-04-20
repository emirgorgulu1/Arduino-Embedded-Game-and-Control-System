# 🎮 Arduino Embedded Game & Control System

## 📌 Overview
This project is a multifunctional embedded system developed using an Arduino Nano. It combines user interaction, real-time processing, audio output, and hardware control into a single integrated platform.

The system provides a menu-driven interface via an OLED display and allows the user to access different functionalities such as games, melody playback, and a countdown-based control mechanism.

---

## 🚀 Features

- 🖥️ OLED graphical interface (SSD1306)
- 🎮 Embedded mini-games:
  - Dino Game (jump mechanics & collision detection)
  - TikTak Game (real-time paddle & ball physics)
- 🔊 Audio system:
  - Buzzer for alerts
  - Speaker with amplifier for melodies
- ⏱️ Countdown-based control system
- ⚡ Dual relay control
- 🎛️ Adjustable volume system
- 🧭 Multi-button navigation interface

---

## 🧩 System Architecture

The system is designed using a modular approach:

### 1. User Interface Module
- OLED display for menu and graphics
- Bitmap-based rendering
- Animation support

### 2. Input Module
- 4 push buttons (Enter, Next, Back, ESC)
- Debounced input handling

### 3. Audio Module
- Buzzer for system feedback
- Amplifier-driven speaker for melodies
- Software-based volume control

### 4. Game Engine Module
- Real-time game loop
- Physics simulation (gravity, velocity)
- Collision detection
- Score tracking system

### 5. Control Module
- Countdown timer mechanism
- Relay-based triggering system
- Safe control without external load connection

---

## 🛠️ Hardware Components

- Arduino Nano
- OLED Display (SSD1306, I2C)
- Push Buttons (x4)
- Buzzer
- Speaker + Amplifier (LM386 or equivalent)
- Relay Modules (x2)
- 10kΩ Resistors (for button pull-down)

---

## 🔌 Circuit Description

- Buttons are connected using **pull-down resistors (10kΩ)**  
- OLED communicates via **I2C (A4 = SDA, A5 = SCL)**  
- Speaker is driven through an **amplifier circuit**  
- Relays are used for control purposes only (no external load connected)  

---

## 💻 Software & Technologies

- Embedded C (Arduino IDE)
- Finite State Machine (FSM)
- Real-time timing using `millis()`
- PROGMEM memory optimization
- Custom audio generation

---

## 🧠 Key Technical Concepts

- Finite State Machine (FSM) design
- Real-time embedded systems
- Game loop architecture
- Collision detection algorithms
- Dynamic difficulty scaling
- Hardware-software integration

---

## 🎮 Usage

### Controls:
- **ENTER** → Select / Confirm  
- **NEXT** → Navigate forward  
- **BACK** → Navigate backward  
- **ESC** → Exit / Return  

### Modes:
- 🎵 Melody Player  
- ⏱️ Countdown System  
- 🎮 Games (Dino & TikTak)  
- ⚙️ Settings  

---

## 📷 Project Demonstration
Real hardware implementation is shown below:

*(Add your project photo here)*

---
## 🎥 Project Videos

▶️ **System Usage Demo**  
[kullanım.mp4](kullanım.mp4)

▶️ **Countdown System Demo**  
[patlama.mp4](patlama.mp4)
## 📌 Future Improvements

- Bluetooth connectivity
- Data logging / score saving
- Additional game modes
- Mobile app integration

---

## 👤 Author

**Emir Görgülü**  
Student ID: 210202012  

---

## 📎 Repository

This repository contains all source code and documentation for the project.

---
