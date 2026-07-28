// Left side motors (paired) - Channel A
const int enableLeft = 9;
const int in1Left = 8;
const int in2Left = 7;

// Right side motors (paired) - Channel B
const int enableRight = 10;
const int in1Right = 6;
const int in2Right = 5;

const int speed = 200; // 0-255

void setup() {
  pinMode(enableLeft, OUTPUT);
  pinMode(in1Left, OUTPUT);
  pinMode(in2Left, OUTPUT);
  pinMode(enableRight, OUTPUT);
  pinMode(in1Right, OUTPUT);
  pinMode(in2Right, OUTPUT);
}

void forward() {
  digitalWrite(in1Left, HIGH);
  digitalWrite(in2Left, LOW);
  digitalWrite(in1Right, HIGH);
  digitalWrite(in2Right, LOW);
  analogWrite(enableLeft, speed);
  analogWrite(enableRight, speed);
}

void backward() {
  digitalWrite(in1Left, LOW);
  digitalWrite(in2Left, HIGH);
  digitalWrite(in1Right, LOW);
  digitalWrite(in2Right, HIGH);
  analogWrite(enableLeft, speed);
  analogWrite(enableRight, speed);
}

void turnRight() {
  // left side forward, right side backward (pivot turn)
  digitalWrite(in1Left, HIGH);
  digitalWrite(in2Left, LOW);
  digitalWrite(in1Right, LOW);
  digitalWrite(in2Right, HIGH);
  analogWrite(enableLeft, speed);
  analogWrite(enableRight, speed);
}

void turnLeft() {
  // right side forward, left side backward (pivot turn)
  digitalWrite(in1Left, LOW);
  digitalWrite(in2Left, HIGH);
  digitalWrite(in1Right, HIGH);
  digitalWrite(in2Right, LOW);
  analogWrite(enableLeft, speed);
  analogWrite(enableRight, speed);
}
void alternateTurns(unsigned long totalMs, unsigned long stepMs) {
  unsigned long elapsed = 0;
  bool right = true;
  while (elapsed < totalMs) {
    if (right) turnRight(); else turnLeft();
    delay(stepMs);
    elapsed += stepMs;
    right = !right;
  }
}
void stopMotors() {
  analogWrite(enableLeft, 0);
  analogWrite(enableRight, 0);
}

void setupSequenceDone() {
  while (true) {} // halt here once sequence finishes
}

void loop() {
  forward();
  delay(30000);
  backward();
  delay(60000);
  alternateTurns(60000, 15000); // 1 minute total, switching every 15s
  stopMotors();
  setupSequenceDone();
}
