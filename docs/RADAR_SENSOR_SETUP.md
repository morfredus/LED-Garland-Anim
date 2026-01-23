# Motion Detection with Doppler Radar (RCWL-0516) - LED-Garland-Anim v5.6.0

## Overview
The RCWL-0516 module is a microwave Doppler radar sensor that enables fast and precise motion detection—even through some non-metallic materials. It is a more responsive and temperature-insensitive alternative to the PIR sensor.

## Wiring
- **VCC**: 3.3 V or 5 V (ESP32 compatible)
- **GND**: Ground
- **OUT**: GPIO 35 (or any digital input on the ESP32)
- **CDS** (optional): Leave floating or connect to GND for continuous detection

## Example Code (PIR replacement)
```cpp
#define RADAR_PIN 35  // GPIO used for RCWL-0516 OUT

void setup() {
  pinMode(RADAR_PIN, INPUT);
  // ...other initializations...
}

void loop() {
  bool motion = digitalRead(RADAR_PIN) == HIGH;
  if (motion) {
    // Trigger animation or desired action
  }
  // ...other processing...
}
```

## Integration Tips
- Detects through thin plastic, but not metal.
- Avoid placing the module near power supplies or metal objects.
- Sensitive to movement behind thin walls—adjust placement as needed.
- Range can be reduced by adding a resistor to the "R-GN" pad.

## Advantages
- Very fast and precise detection
- Not affected by ambient temperature
- Wide detection angle (~120°)

## Limitations
- No built-in physical sensitivity adjustment (but can be modified with a resistor)
- May detect through thin non-metallic walls (beware of false positives)

## To be integrated into the firmware and user documentation if this sensor is adopted as an official option.
