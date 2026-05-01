// ----------- BLYNK CONFIG -----------
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""


#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

// ----------- WIFI -----------
char ssid[] = "";
char pass[] = "";

// ----------- DHT22 -----------
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ----------- SENSOR PINS -----------
const int mq135Pin = 1;
const int soundPin = 2;

// ----------- TIMER -----------
BlynkTimer timer;

// ----------- MQ135 -----------
float readMQ135() {
  int val = analogRead(mq135Pin);
  float ppm = (val / 4095.0) * 500; // rough estimation
  Serial.print("Raw MQ135 Value: ");
Serial.println(val);
  return ppm;
  
}

// ----------- SOUND -----------
float readSound() {
  int val = analogRead(soundPin);
  float level = (val / 4095.0) * 100;
  return level;
}

// ----------- HEAT INDEX -----------
float calculateHeatIndex(float t, float h) {
  float tempF = (t * 1.8) + 32;

  if (tempF < 80.0 || h < 40.0) return t;

  float hi = -42.379 +
             2.04901523 * tempF +
             10.14333127 * h -
             0.22475541 * tempF * h -
             0.00683783 * pow(tempF, 2) -
             0.05481717 * pow(h, 2) +
             0.00122874 * pow(tempF, 2) * h +
             0.00085282 * tempF * pow(h, 2) -
             0.00000199 * pow(tempF, 2) * pow(h, 2);

  return (hi - 32) / 1.8;
}

// ----------- MAIN FUNCTION -----------
void sendSensorData() {

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT22 read failed!");
    return;
  }

  float air = readMQ135();
  float sound = readSound();
  float heatIndex = calculateHeatIndex(temperature, humidity);

  // -------- SERIAL DEBUG --------
  Serial.print("Temp: "); Serial.print(temperature);
  Serial.print(" C | Hum: "); Serial.print(humidity);
  Serial.print(" % | Air: "); Serial.print(air);
  Serial.print(" ppm | Sound: "); Serial.print(sound);
  Serial.print(" % | HI: "); Serial.println(heatIndex);

  // -------- BLYNK --------
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, heatIndex);
  Blynk.virtualWrite(V3, air);
  Blynk.virtualWrite(V4, sound);
}

// ----------- SETUP -----------
void setup() {
  Serial.begin(115200);

  analogReadResolution(12); // better ADC

  dht.begin();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // DHT22 needs delay → 2 seconds
  timer.setInterval(2000L, sendSensorData);
}

// ----------- LOOP -----------
void loop() {
  Blynk.run();
  timer.run();
}
