/*
Name : Arundev Annath
Date : 03/03/2024
Objective : To connect a LM35 temperature sensor with an arduino UNO
*/
#include <TimerOne.h>

const int temperaturePin = A0;  // Analog pin for LM35 temperature sensor
const int ledPin = 13;          // Onboard LED pin

const int belowThresholdBlinkInterval = 250;  // Blink interval when temperature is below 30 degrees Celsius
const int aboveThresholdBlinkInterval = 500;  // Blink interval when temperature is above 30 degrees Celsius

const int temperatureThreshold = 30;  // Temperature threshold in degrees Celsius

void setup() {
  pinMode(ledPin, OUTPUT);
  Timer1.initialize(1000);  // Initialize Timer1 with a 1s (1000ms) period
  Timer1.attachInterrupt(timerCallback);  // Attach the timer callback function
  Serial.begin(9600);
}

void loop() {
  int temperature = readTemperature();
  
  if (temperature < temperatureThreshold)
  {
    Timer1.setPeriod(belowThresholdBlinkInterval * 1000);  // Set the timer period for below threshold
  } 
  else 
  {
    Timer1.setPeriod(aboveThresholdBlinkInterval * 1000);  // Set the timer period for above threshold
  }

  delay(100);  // Add a small delay to stabilize the temperature readings
}

void timerCallback() {
  static bool ledState = LOW;
  digitalWrite(ledPin, ledState);
  ledState = !ledState;
}

int readTemperature() {
  // Read the analog value from LM35 temperature sensor
  int sensorValue = analogRead(temperaturePin);

  // Convert the analog value to temperature in degrees Celsius
  float temperatureCelsius = (sensorValue / 1024.0) * 500.0;

  Serial.print("Temperature: ");
  Serial.print(temperatureCelsius);
  Serial.println(" °C");

  return temperatureCelsius;
}
