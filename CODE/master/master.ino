#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);
unsigned long lastSend = 0;

// Nút D4: toggle O/o cho servo5
const int BUTTON1_PIN = 4;
bool lastButton1State = HIGH;
bool toggleState = false;           // false = 0°, true = 120°
unsigned long lastDebounceTime1 = 0;
const unsigned long debounceDelay = 50;

// Nút D7: trigger chạy quy trình 
const int BUTTON2_PIN = 7;
bool lastButton2State = HIGH;
unsigned long lastDebounceTime2 = 0;

void setup() {
  Serial.begin(38400);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  pinMode(BUTTON1_PIN, INPUT_PULLUP);  // D4
  pinMode(BUTTON2_PIN, INPUT_PULLUP);  // D7

  Serial.println("MASTER ready...");
}

void loop() {
  //  Xử lý nút D4: gửi 'O' / 'o'
  bool b1 = digitalRead(BUTTON1_PIN);
  if (b1 != lastButton1State) {
    lastDebounceTime1 = millis();
    lastButton1State = b1;
  }
  if ((millis() - lastDebounceTime1) > debounceDelay) {
    if (b1 == LOW) {
      toggleState = !toggleState;                // đổi trạng thái
      Serial.println(toggleState ? "O" : "o");   // gửi lệnh cho servo5
      while (digitalRead(BUTTON1_PIN) == LOW) { delay(1); } // chờ nhả
    }
  }

  // Xử lý nút D7: gửi "TEST2" 
  bool b2 = digitalRead(BUTTON2_PIN);
  if (b2 != lastButton2State) {
    lastDebounceTime2 = millis();
    lastButton2State = b2;
  }
  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (b2 == LOW) {
      Serial.println("TEST2");                    // trigger quy trình test2 trên SLAVE
      while (digitalRead(BUTTON2_PIN) == LOW) { delay(1); } // chờ nhả
    }
  }
 // Gửi dữ liệu từ MPU
  mpu6050.update();
  int x = mpu6050.getAngleX();
  int y = mpu6050.getAngleY();

  if (millis() - lastSend >= 20) { // ~50 Hz
    Serial.print(x);
    Serial.print(',');
    Serial.print(y);
    Serial.print('\n');
    lastSend = millis();
  }
}
