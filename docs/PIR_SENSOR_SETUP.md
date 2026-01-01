# Recommended settings for this project

For the LED-Garland-Anim project, the optimal PIR sensor settings are:

- **Sensitivity**: Medium to high ("Sx" potentiometer turned about 2/3 clockwise). This reliably detects human presence at 2–4 meters.
- **Time Delay**: Short to medium ("Tx" potentiometer set between 2 and 5 seconds). The garland turns off quickly after leaving, while remaining responsive.
- **Jumper (Trigger Mode)**: Set to "H" (repeat trigger, sometimes labeled "Repeat/Trigger"). Animation remains active as long as motion is detected.

**Summary:**
- Sensitivity: 2/3 (medium/high)
- Time Delay: 2–5 s
- Jumper: "H" mode (repeat)

These settings ensure reliable detection and the best user experience for the LED garland animation.

# PIR Sensor Setup & Adjustment (HC-SR501)

## Overview
The PIR sensor (HC-SR501) is used to detect motion and trigger the LED garland. Proper installation and adjustment are essential for reliable operation.

## Wiring
- **VCC**: Connect to 5V (ESP32 5V pin)
- **GND**: Connect to ground
- **OUT**: Connect to GPIO 35 (input-only pin on ESP32 IdeaSpark)

## Physical Adjustments
### 1. Sensitivity
- **Potentiometer marked "Sx" or "Sens"**
- Turn clockwise to increase detection range (up to ~6m)
- Turn counterclockwise to decrease range
- Adjust according to room size and desired detection distance

### 2. Time Delay (Hold Time)
- **Potentiometer marked "Tx" or "Time"**
- Sets how long the output stays HIGH after motion is detected (from a few seconds to several minutes)
- For this project, the software manages the activation duration, but the physical setting can affect responsiveness

### 3. Jumper (Trigger Mode)
- **H (Repeat Trigger)**: Output stays HIGH as long as motion is detected
- **L (Single Trigger)**: Output goes HIGH once, then waits for the delay to expire before rearming
- For continuous detection, set the jumper to "H"

## Installation Tips
- Avoid direct sunlight, heaters, or air vents
- Mount at human height for optimal detection
- Test sensitivity and delay to avoid false triggers

## Troubleshooting
- If always triggered: reduce sensitivity, move away from heat sources
- If never triggered: increase sensitivity, check wiring
- If output is unstable: check power supply and common ground

---
**Document version: v1.11.2 (2025-12-31)**