#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int MQ8_PIN = A0;
const int BUZZER_PIN = 8;
const int LED_RED_PIN = 9;
const int LED_GREEN_PIN = 10;

const int GAS_THRESHOLD = 400;

void setup() {
  pinMode(MQ8_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);

  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("Gas Detector");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  int gasLevel = analogRead(MQ8_PIN);

  lcd.setCursor(0, 0);
  lcd.print("Gas Level: ");
  lcd.print(gasLevel);
  lcd.print("   ");

  if (gasLevel > GAS_THRESHOLD) {
    digitalWrite(LED_RED_PIN, HIGH);
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(BUZZER_PIN, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Status: ALERT! ");
  } else {
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Status: Normal ");
  }

  delay(500);
}
