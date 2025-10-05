// -------------------------------------------------------------
// Project: MQ3 Sensor Alcohol Detector using Arduino UNO
// Components: MQ3 Sensor, Buzzer, LED, LCD 16x2
// Author: Ujwal Lekurwale
// -------------------------------------------------------------

#include <LiquidCrystal.h>

// Pin Definitions
#define MQ3_PIN A0     // Analog input from MQ3 sensor
#define BUZZER_PIN 8   // Digital pin for buzzer
#define LED_PIN 9      // Digital pin for warning LED

// LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Variables
int sensorValue = 0;
int alcoholThreshold = 350;  // Adjust threshold after calibration

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print(" Alcohol Detector ");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();

  lcd.print("Ready to detect");
  Serial.println("MQ3 Alcohol Detector Ready");
}

void loop() {
  sensorValue = analogRead(MQ3_PIN);
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  lcd.setCursor(0, 0);
  lcd.print("Value: ");
  lcd.print(sensorValue);
  lcd.print("   ");

  // Check alcohol level
  if (sensorValue > alcoholThreshold) {
    lcd.setCursor(0, 1);
    lcd.print("ALCOHOL DETECTED!");
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000); // Sound alert
    delay(2000);
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Safe: No Alcohol ");
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }

  delay(500);
}
