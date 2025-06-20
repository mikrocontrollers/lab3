#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int Vpin = A5;
float voltage;
float volts;

float previousVolts = 0.0;
const float threshold = 0.2;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  delay(2000);
  lcd.clear();
}

void loop() {
  volts = readAverageVoltage(Vpin);
  
  if (abs(volts - previousVolts) > threshold) {
    previousVolts = volts;
    displayVoltage(volts);
  }
  delay(1000);
}

float readAverageVoltage(int pin) {
  long sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(pin);
    delay(5);
  }
  float rawVoltage = (sum / 10.0) / 1023.0 * 5.0;
  return rawVoltage;
}

void displayVoltage(float volts) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Voltage: ");
  lcd.print(volts, 2);
  lcd.print(" V");

  String jsonData = "{\"value\":";
  jsonData += String(volts, 2);
  jsonData += "}";

  Serial.println(jsonData);
}