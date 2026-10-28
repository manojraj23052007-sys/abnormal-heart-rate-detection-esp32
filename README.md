# Abnormal Heart Rate Detection and Alert System Using ESP32

## Project Overview

This project demonstrates an abnormal heart rate detection and alert system using an ESP32 microcontroller. The system displays synthetic heart rate values and status on a 16x2 I2C LCD. An LED and buzzer provide an alert when the reading remains outside the configured range.

## Components Used

* ESP32 DevKit
* 16x2 I2C LCD
* LED
* 220-ohm resistor
* Buzzer
* Velxio simulator

## Pin Connections

| Component | ESP32 Pin |
| --------- | --------- |
| LCD SDA   | GPIO 21   |
| LCD SCL   | GPIO 22   |
| LED       | GPIO 25   |
| Buzzer    | GPIO 26   |

## Working Principle

1. The ESP32 generates synthetic heart rate values for demonstration.
2. The LCD displays the heart rate and its status.
3. The configured normal range is 60–100 BPM.
4. If an abnormal reading continues for the configured delay, the LED and buzzer are activated.
5. When the reading returns to the configured normal range, the alert is deactivated.

## Software and Tools

* Arduino-style C++
* ESP32
* Velxio simulator
* LiquidCrystal_I2C library

## Future Improvements

* Integration with Blynk IoT
* Real heart rate sensor integration
* Mobile monitoring and notifications

## Important Note

This project currently uses synthetic heart rate readings for simulation. It does not measure actual heart rate and is not intended for medical diagnosis.
