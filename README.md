1. Introduction

This project implements a sensor–actuator control system using an Arduino Uno.
Multiple sensors are used to measure light intensity, flex/bend, and temperature–humidity.
Based on the sensor readings, different actuators such as LEDs, a servo motor, a buzzer, and an OLED display respond automatically.

This project was created as part of the FOSSEE Arduino Internship screening task (Task - 1)

2. Components Used
	•	Arduino Uno
	•	Breadboard
	•	SSD1306 OLED Display (I2C)
	•	LDR (Light Dependent Resistor)
	•	Flex Sensor
	•	DHT11 Temperature & Humidity Sensor
	•	Servo Motor (SG90)
	•	Active Buzzer (3-pin)
	•	LEDs (2 units)
	•	Resistors (1kΩ and 10kΩ)
	•	Jumper Wires

3. System Features

LDR to LED

The LDR monitors ambient light.
If the light level falls below a threshold, LED1 switches ON.
Otherwise, it remains OFF.

Flex Sensor to Servo

When the flex sensor is bent beyond a threshold, the servo rotates to 120°.
When the sensor is straight, the servo returns to 0°.

DHT11 to LED and Buzzer

If the measured temperature rises above 30°C, LED2 turns ON and the buzzer activates.
This serves as a simple temperature alert mechanism.

OLED Display

The OLED shows all sensor readings in real time:
	•	LDR value
	•	Flex sensor value
	•	Temperature
	•	Humidity
	•	Servo status
	•	Buzzer status

Serial Monitor Output

All readings are also printed to the Serial Monitor at 115200 baud.

4. Pin Connections

Sensors

Sensor:                                Arduino Pin
LDR (voltage divider output)	         A0
Flex Sensor (voltage divider output)	 A1
DHT11 (DATA pin)	                     D2

Actuators:

Actuator	                             Arduino Pin
Servo Motor	                           D3
Buzzer (signal)	                       D9
LED1 (LDR indicator)	                 D10
LED2 (temperature indicator)	         D11

OLED Display (I2C)

OLED 	                                 Arduino Pin
SDA	                                   A4
SCL	                                   A5
VCC	                                   5V
GND	                                   GND


7. How to Run the Project
	1.	Clone the repository
	2.	Open the .ino file in Arduino IDE
	3.	Install the required libraries:
	Adafruit SSD1306
	Adafruit GFX
	DHT Sensor Library
	4.	Connect the circuit as shown in the diagram
	5.	Upload the code
	6.	Open the Serial Monitor (115200 baud)
	7.	Test each sensor:
	Cover/uncover the LDR
	Bend the flex sensor
	Warm the DHT11 to trigger the buzzer


9. Future Improvements 
Adding Bluetooth or WiFi monitoring using ESP32
Adding more environmental sensors
Logging data to SD card

Author

Avnish Vidyarthi
ECE Student — VIT Bhopal
