# Guntroller 



## Overview
**Guntroller** is a DIY motion-sensing game controller designed for FPS (First Person Shooter) games. Instead of using a traditional mouse or thumbstick to aim, this controller uses an **MPU6050 Gyroscope** to translate physical movements into mouse cursor inputs.

It features dynamic sensitivity scaling (Sniper Mode vs. Quick Turn), integrated weapon switching, and standard keyboard macros, making it a fully functional plug-and-play gaming device.

## Features
* **Gyro-Based Aiming:** Rotational movement (Yaw/Pitch) translates directly to mouse X/Y movement.
* **Dynamic Sensitivity:**
    * **Precision Mode:** Lowers sensitivity for sniping.
    * **Quick Mode:** Increases sensitivity for fast turns.
* **Integrated Key Mapping:** Dedicated buttons for specific game actions (Esc, 'B' key, Weapon Switch).
* **Plug & Play:** Uses the Arduino `Mouse.h` and `Keyboard.h` libraries to act as a standard HID device (no drivers needed).

## Hardware Requirements
* **Microcontroller:** Arduino Pro Micro, Leonardo, R4 Minima or any ATmega32u4/Renesas RA4M1 board. (Must support USB HID).
* **Sensor:** MPU6050 (Accelerometer + Gyroscope).
* **Buttons:** 7x Momentary Push Buttons.
* **Wires & Breadboard/PCB.**

## Pinout & Wiring

| Component | Arduino Pin | Function |
| :--- | :--- | :--- |
| **MPU6050 SDA** | `SDA` (R4 Minima) | I2C Data |
| **MPU6050 SCL** | `SCL` (R4 Minima) | I2C Clock |
| **Button 1** | `4` | **Fire** (Left Mouse Click) |
| **Button 2** | `7` | **Pause Menu** (ESC Key) |
| **Button 3** | `8` | **Precision Mode** (Low Sensitivity) |
| **Button 4** | `9` | **Quick Mode** (High Sensitivity) |
| **Button 5** | `10` | **Steady Aim** (Stops Cursor/Reset) |
| **Button 6** | `11` | **Action** ('B' Key) |
| **Button 7** | `12` | **Next Weapon** (Scroll Wheel Up) |

*> **Note:** All buttons are configured as `INPUT_PULLUP`. Wire one leg of the button to the Pin, and the other leg to GND.*

## Software & Libraries
This project relies on the following libraries (available via Arduino Library Manager):
1.  **Adafruit MPU6050**
2.  **Adafruit Unified Sensor**
3.  **Mouse.h** (Built-in)
4.  **Keyboard.h** (Built-in)

### Installation
1.  Open the `.ino` file in the Arduino IDE.
2.  Go to **Sketch > Include Library > Manage Libraries**.
3.  Search for and install `Adafruit MPU6050`.
4.  Select your board: **Tools > Board > Arduino AVR Boards > Arduino Leonardo (or Pro Micro)**.
5.  Upload the code.
6.  *Keep the controller flat* during the first 2 seconds of startup for sensor calibration.

## How It Works (The Math)
The code reads raw Gyro Z and Gyro Y data to calculate cursor movement:
```cpp
float dx = 100 * g.gyro.z; // Horizontal movement
float dy = 100 * g.gyro.y; // Vertical movement
```
## Sensitivity Logic
* **Normal:** Base calculation.

* **Precision (Pin 8):** Movement / 2 (Slower, accurate).

* **Quick Mode (Pin 9):** Movement * 2 (Faster, reflex shots).

* **Reset (Pin 10):** Movement = 0 (Locks cursor for manual caliberation).

## ⚠️ Important: Sensor Orientation
**The physical placement of the MPU6050 is critical for this code to work correctly.**

The code is written assuming the sensor is mounted **flat** (parallel to the ground) relative to the controller's "barrel."

* **Yaw (Z-Axis):** Rotating the gun Left/Right moves the mouse Left/Right.
* **Pitch (Y-Axis):** Tilting the gun Up/Down moves the mouse Up/Down.



**If you mount the sensor sideways or vertically:**
Your controls will be messed up (e.g., tilting up might make the mouse go left). You will either need to remount the sensor or modify lines `63` and `64` in the code to swap `g.gyro.z` and `g.gyro.y` to match your mounting angle.

## For movement keys (w a s d shift etc) a simple esp32 based bluetooth pedalboard is used. 

