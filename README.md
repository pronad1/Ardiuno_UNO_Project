# IoT Smart Plant Monitoring System

## Project Overview
The **IoT Smart Plant Monitoring System** is a low-cost, standalone embedded solution designed to monitor plant health remotely. The system uses an **ATmega328P microcontroller** (the core chip of Arduino Uno) on a breadboard to read environmental data and transmit it to the **Blynk IoT Cloud** via an **ESP8266 Wi-Fi module**.

Users can monitor **Soil Moisture**, **Temperature**, **Humidity**, and **Water Density** in real-time through the Blynk Mobile App. The system also features **Manual Water Pump Control** via the app and an **Audio Buzzer Alert** that triggers automatically when the soil is completely dry.

## Key Features
* **Real-Time Monitoring:** View Temp, Humidity, Soil Moisture, and Water Density on your phone.
* **Remote Control:** Turn the Water Pump ON/OFF manually from anywhere in the world.
* **Emergency Alert:** A Buzzer sounds automatically if soil moisture drops to 0% (Critical Dry).
* **Standalone Design:** Built on a breadboard using the ATmega328P chip (No Arduino Board required).
* **Wi-Fi Connectivity:** Uses ESP8266-01 as a Wi-Fi modem.

## Hardware Components
1. **Microcontroller:** ATmega328P-PU (Standalone configuration).
2. **Wi-Fi Module:** ESP8266-01.
3. **Sensors:**
   * **DHT11** (Temperature & Humidity).
   * **Soil Moisture Sensor** (Analog).
   * **Turbidity/Water Density Sensor** (Analog).
4. **Actuators:**
   * 5V Relay Module (for Water Pump).
   * Mini Submersible Water Pump.
   * Active Buzzer.
5. **Power & Circuitry:**
   * 16 MHz Crystal Oscillator & 22pF Capacitors (x2).
   * 10kΩ Resistor (Pull-up for Reset).
   * 1kΩ & 2kΩ Resistors (Voltage Divider for ESP RX).
   * 5V & 3.3V Power Supply (External).

## Pin Configuration Map
| Component | Code Pin | Physical Leg | Description |
| :--- | :--- | :--- | :--- |
| **ESP8266 TX** | D2 | Pin 4 | RX (SoftwareSerial) |
| **ESP8266 RX** | D3 | Pin 5 | TX (Via Voltage Divider) |
| **Buzzer** | D4 | Pin 6 | Positive Leg (+) |
| **DHT11** | D5 | Pin 11 | Data Signal |
| **Water Pump** | D6 | Pin 12 | Relay IN Pin |
| **Soil Sensor** | A0 | Pin 23 | Analog Signal |
| **Density Sensor** | A1 | Pin 24 | Analog Signal |
| **Reset** | -- | Pin 1 | Connect to 5V via 10k Resistor |
| **Crystal** | -- | Pin 9 & 10 | 16MHz Oscillator |
| **Power (VCC)** | -- | Pin 7 & 20 | Connect to +5V |
| **Ground (GND)** | -- | Pin 8 & 22 | Connect to GND |

## Blynk App Setup
Configure your Blynk Dashboard with the following Datastreams:

| Widget Name | Type | Pin | Min | Max |
| :--- | :--- | :--- | :--- | :--- |
| **Temperature** | Gauge | V0 | 0 | 50 |
| **Humidity** | Gauge | V1 | 0 | 100 |
| **Soil Moisture** | Gauge | V3 | 0 | 100 |
| **Water Density** | Gauge | V6 | 0 | 1000 |
| **Pump Control** | Switch | V12 | 0 | 1 |

## Important Wiring Notes
1. **Power Supply is Critical:**
   * The **ATmega328P** requires **5V**.
   * The **ESP8266** requires **3.3V**. Connecting it to 5V will burn it.
   * **Solution:** Use a 5V source for the main rails and a 3.3V Regulator (LD33V) or the "Diode Drop" method for the ESP8266.

2. **ESP8266 Protection:**
   * The Arduino TX (5V) cannot go directly to ESP RX (3.3V). You **must** use a voltage divider (1kΩ + 2kΩ resistors) or a logic level shifter.

3. **Common Ground:**
   * Ensure the Ground (GND) of your external battery, the ESP8266, the sensors, and the ATmega328P are all connected together.

## Libraries Required
1. **Blynk** (by Volodymyr Shymanskyy).
2. **DHT sensor library** (by Adafruit).
3. **Adafruit Unified Sensor** (by Adafruit).

## How to Run
1. Assemble the circuit on the breadboard following the Pin Map.
2. Open the `.ino` file in Arduino IDE.
3. Update the **WiFi Credentials** and **Blynk Auth Token** in the code.
4. Select board: **"Arduino Uno"**.
5. Upload the code via an external programmer (or Arduino as ISP).
