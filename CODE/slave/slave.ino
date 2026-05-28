#include <Servo.h>

// ===== Servo =====
Servo servo1;  // 11
Servo servo2;  // 10
Servo servo3;  // 9
Servo servo4;  // 5
Servo servo5;  // 3

int x = 0, y = 0;
int val1 = 90, val2 = 90, val3 = 90, val4 = 20, val5 = 0;

struct Pose {
  int a[5];            // góc 5 servo
  uint32_t tgdichuyen;    // thời gian chuyển động đến pose
  uint32_t tghold;    // thời gian giữ pose
};


const bool LOOP_SEQUENCE = true;
Pose sequence[] = {           //<---- Sửa hành trình di chuyển của tay máy
  { {  80, 55, 110, 45,   0 }, 1000, 500 },  // Pose 0   {{khớp 1, khớp 2, khớp 3, khớp 4, khớp 5}, tgian di chuyển, tgian dừng pose},
  { {  45, 60, 140,  0,   0 }, 1000, 500 },  // Pose 1
  { {  45, 60, 140,  0, 120 },  500, 500 },  // Pose 2
  { { 135, 60, 140,  0, 120 }, 1000, 500 },  // Pose 3
  { { 135, 60, 140,  0,   0 },  500, 500 },  // Pose 4
};
const int SEQ_COUNT = sizeof(sequence)/sizeof(sequence[0]);

bool seqRunning = false;
bool seqInHold  = false;
int  seqIndex   = 0;
unsigned long seqPhaseStart = 0;
int startAngle[5] = {90,90,90,20,0};   
int currAngle[5]  = {90,90,90,20,0};   

int clampAngle(int a) {
  if (a < 0) a = 0;
  if (a > 180) a = 180;
  return a;
}

void writeAllServos(const int a[5]) {
  servo1.write(a[0]);
  servo2.write(a[1]);
  servo3.write(a[2]);
  servo4.write(a[3]);
  servo5.write(a[4]);
}

void startTest2Sequence() {
  seqRunning = true;
  seqIndex   = 0;

  // Khởi động bằng easing từ góc hiện tại (val1..val5) -> pose 0
  startAngle[0] = val1; startAngle[1] = val2; startAngle[2] = val3;
  startAngle[3] = val4; startAngle[4] = val5;

  for (int i = 0; i < 5; ++i) currAngle[i] = startAngle[i];
  writeAllServos(currAngle);

  seqInHold = false;                 // vào PHA MOVE tới sequence[0]
  seqPhaseStart = millis();
  Serial.println("TEST2 -> START (ease to pose 0)");
}

void stopTest2Sequence() {
  seqRunning = false;

  // Reset về pose 0 trước khi trả tay
  for (int i = 0; i < 5; ++i) {
    currAngle[i] = clampAngle(sequence[0].a[i]);
  }
  writeAllServos(currAngle);

  // Đồng bộ biến điều khiển tay theo pose 0
  val1 = currAngle[0];
  val2 = currAngle[1];
  val3 = currAngle[2];
  val4 = currAngle[3];
  val5 = currAngle[4];

  Serial.println("TEST2 -> STOP & RESET pose 0");
}

void stepTest2Sequence() {
  if (!seqRunning || SEQ_COUNT == 0) return;
  unsigned long now = millis();

  if (seqInHold) {
    uint32_t holdDur = sequence[seqIndex].tghold;
    if (now - seqPhaseStart >= holdDur) {
      // Sang pose kế
      int next = seqIndex + 1;
      if (next >= SEQ_COUNT) {
        if (LOOP_SEQUENCE) {
          // Wrap về pose 0 bằng easing
          for (int i = 0; i < 5; ++i) startAngle[i] = currAngle[i];
          seqIndex = 0;          // mục tiêu là pose 0
          seqInHold = false;     // chuyển sang pha MOVE
          seqPhaseStart = now;   // bắt đầu nội suy mới
        } else {
          stopTest2Sequence();
        }
        return;
      }
      // chuyển sang MOVE tới pose next
      for (int i = 0; i < 5; ++i) startAngle[i] = currAngle[i];
      seqIndex = next;
      seqInHold = false;
      seqPhaseStart = now;
    }
    return;
  }

  // Di chuyển sang pose seqIndex
  uint32_t mvDur = sequence[seqIndex].tgdichuyen;
  uint32_t elapsed = now - seqPhaseStart;
  float t = (mvDur > 0) ? (float)elapsed / (float)mvDur : 1.0f;
  if (t < 0) t = 0;
  if (t > 1.0f) t = 1.0f;

  // cubic 
  float e = t * t * (3 - 2 * t);

  for (int i = 0; i < 5; ++i) {
    float a0 = (float)startAngle[i];
    float af = (float)clampAngle(sequence[seqIndex].a[i]);
    float a  = a0 + (af - a0) * e;
    currAngle[i] = (int)(a + 0.5f);
  }
  writeAllServos(currAngle);

  if (t >= 1.0f) {
    seqInHold = true;
    seqPhaseStart = now;
    // đồng bộ val1..val5 để khi dừng có trạng thái đúng
    val1 = currAngle[0]; val2 = currAngle[1]; val3 = currAngle[2];
    val4 = currAngle[3]; val5 = currAngle[4];
  }
}

// ===== Helpers =====
void doclenh(const String& line) {
  // 1) Lệnh O/o cho servo5
  if (line == "O") { val5 = 120; Serial.println("S5->120 (button)"); return; }
  if (line == "o") { val5 = 0;   Serial.println("S5->0 (button)");   return; }

  // 2) TEST2 toggle
  if (line == "TEST2") {
    if (seqRunning) stopTest2Sequence();
    else            startTest2Sequence();
    return;
  }

  // 3) x,y (chỉ nhận khi không chạy TEST2)
  int comma = line.indexOf(',');
  if (comma > 0) {
    x = line.substring(0, comma).toInt();
    y = line.substring(comma + 1).toInt();
    if (seqRunning) return; // đang chạy chuỗi thì bỏ qua dữ liệu tay
    val1 = map(x, -45, 45, 0, 180);
    val2 = map(y, -45, 45, 135, 55);
    val3 = map(y, -45, 45, 90, 150);
    val4 = map(y, -45, 45, 45, 0);

    Serial.print("x: "); Serial.print(x);
    Serial.print(" | y: "); Serial.print(y);
    Serial.print(" || val1: "); Serial.print(val1);
    Serial.print(" | val2: "); Serial.print(val2);
    Serial.print(" | val3: "); Serial.print(val3);
    Serial.print(" | val4: "); Serial.print(val4);
    Serial.print(" | val5: "); Serial.println(val5);
  }
}

// ===== Setup =====
void setup() {
  Serial.begin(38400);   // khớp với MASTER
  servo1.attach(11);
  servo2.attach(10);
  servo3.attach(9);
  servo4.attach(5);
  servo5.attach(3);
  Serial.println("SLAVE ready...");
}

// ===== Loop =====
void loop() {
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    line.trim();
    if (line.length() > 0) doclenh(line);
  }

  if (seqRunning) {
    stepTest2Sequence();
  } else {
    // điều khiển bình thường
    servo1.write(constrain(val1, 0, 180));
    servo2.write(constrain(val2, 55, 135));
    servo3.write(constrain(val3, 90, 150));
    servo4.write(constrain(val4, 0, 45));
    servo5.write(constrain(val5, 0, 180));
  }

  delay(10);
}
