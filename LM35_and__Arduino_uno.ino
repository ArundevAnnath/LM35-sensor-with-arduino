/*
Name : Arundev Annath
Date : 03/03/2024
Objective : To connect a LM35 temperature sensor with an arduino UNO
*/


const int lm35Pin = A0;  // LM35 temperature sensor connected to Analog pin A0
const int ledPin = 13;   // Onboard LED connected to digital pin 13

unsigned long previousMillis = 0;
const long intervalLowTemp = 250;   // Blink interval for temperature below 30°C
const long intervalHighTemp = 500;  // Blink interval for temperature above 30°C

void setup() {
  pinMode(lm35Pin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Read temperature from LM35 sensor
  int temperature = readTemperature();

  // Check temperature and control LED blink accordingly
  if (temperature < 30) {
    blinkLED(intervalLowTemp);
  } else {
    blinkLED(intervalHighTemp);
  }
}

int readTemperature() {
  // Read analog value from LM35 and convert it to Celsius
  int sensorValue = analogRead(lm35Pin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperatureC = (voltage - 0.5) * 100.0;

  return (int)temperatureC;
}

void blinkLED(long interval) {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Save the last time we blinked the LED
    previousMillis = currentMillis;

    // Toggle the LED state
    digitalWrite(ledPin, !digitalRead(ledPin));
  }
}
