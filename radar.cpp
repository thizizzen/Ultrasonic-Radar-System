#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int trigPin = 10;
const int echoPin = 11;
long duration;
int distance;
Servo myServo;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myServo.attach(12);
  
  lcd.begin(16, 2);
  lcd.print("Starting...");
  delay(2000);
}

void loop() {
  for (int i = 15; i <= 165; i++) {
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    updateLCD(i, distance);
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }

  for (int i = 165; i > 15; i--) {
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    updateLCD(i, distance);
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}

int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void updateLCD(int angle, int dist) {
  lcd.clear();
  
  lcd.setCursor(0, 0);
  int progress = map(angle, 15, 165, 0, 100);
  lcd.print("Scanning: ");
  lcd.print(progress);
  lcd.print("%");

  lcd.setCursor(0, 1);
  if (dist < 10) {
    lcd.print("Too Close!");
  } else if (dist < 40) {
    lcd.print("Object Detected");
  } else {
    lcd.print("Safe Distance");
  }

  if (dist == 0) {
    lcd.setCursor(0, 1);
    lcd.print("Sensor Error");
  }
}
