/*
Name : Arundev Annath
Date : 03/03/2024
Objective : To connect a LM35 temperature sensor with an arduino UNO
*/

#include <TimerOne.h>

const int temperaturePin = A0;  // Analog pin for LM35 temperature sensor
const int ledPin = 13;          // Onboard LED pin

const int belowThresholdBlinkInterval = 250;  // Blinking interval when temperature is below 30 degrees Celsius
const int aboveThresholdBlinkInterval = 500;  // interval when temperature is above 30 degrees Celsius

const int temperatureThreshold = 30;  // Temperature threshold in degrees Celsius

void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(temperaturePin, INPUT);
  Timer1.initialize(1000);  // Initialize Timer1 with a 1s (1000ms) period
  Timer1.attachInterrupt(timerCallback);  // Attach the timer callback function
  Serial.begin(9600);
}

void loop()
{
  int temperature = readTemperature();
  
  if (temperature < temperatureThreshold)
  {
    Timer1.setPeriod(belowThresholdBlinkInterval * 1000);  // to Set the timer period for below threshold
  } 
  else 
  {
    Timer1.setPeriod(aboveThresholdBlinkInterval * 1000);  // to Set the timer period for above threshold
  }

  delay(100);  // small delay to stabilize the temperature value
}

void timerCallback() 
{
  static bool ledState = LOW;
  digitalWrite(ledPin, ledState);
  ledState = !ledState;
}

int readTemperature()
{

  int sensorValue = analogRead(temperaturePin); // Reading the analog value from LM35 temperature sensor
  float temperatureCelsius = (sensorValue / 1024.0) * 500.0;  //// Converting the analog value to temperature in degrees Celsius
  Serial.print("Temperature: ");
  Serial.print(temperatureCelsius);
  Serial.println(" °C");

  return temperatureCelsius;
}