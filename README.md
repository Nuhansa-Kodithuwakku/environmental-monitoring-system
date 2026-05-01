# environmental-monitoring-system

This project involves developing an IoT-based environmental monitoring system using the ESP32-S3 microcontroller, DHT11 temperature and humidity sensor, MQ-135 gas sensor and ultrasound sensor. The data collected from the sensors is displayed on an I2C LCD and can be sent to a IoT platform for remote monitoring. The system also calculates the heat index and categorizes it into different levels.
# Components
ESP32 - S3 microcontroller
DHT11 humidity and temperature sensor 
Ultra sound sensor
MQ135 gas sensor

# Code structure
1.Libraries and Definitions
Includes necessary libraries and defines pins for sensors and modules.

2.Sensor Initialization
Initializes the DHT11 humidity and temperature sensor, Ultra sound sensor, MQ135 gas sensor

3.Data Collection and Calculation
Reads sensor data, calculates the heat index, and categorizes it.

4.Data Transmission and Display
Sends the data to Blynk platform for user friendly veiw.

# Setup Instructions
## Hardware Connections

Connect the DHT11 sensor to an gpio pin of the ESP32.
Connect the MQ-135 sensor to an analog input pin of the ESP32.
Connect the ultrasound sensor to an analog pin of ESP32.

## Software Setup
- readme
- Install the Blynk library in the Arduino IDE.
- Open the main.ino file in the Arduino IDE.
- Replace "YOUR_BLYNK_AUTH_TOKEN", "YOUR_SSID", and "YOUR_PASSWORD" with your actual Blynk authentication token and Wi-Fi credentials.
- Uploading the Code
- Connect the ESP32 to your computer via USB.
- Select the appropriate board and port in the Arduino IDE.
- Upload the code to the ESP32.
