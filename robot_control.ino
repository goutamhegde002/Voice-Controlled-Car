#include <AFMotor.h>

#define Echo A0
#define Trig A1
#define RedLED 8
#define GreenLED 7

String command;
String lastMovementCommand; // Variable to store the last movement command executed

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

void setup() {
  Serial.begin(9600);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(RedLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
}

void loop() {
  while (Serial.available()) {
    command = Serial.readString();
    Serial.println("Received Command: " + command);
    executeCommand(command);
  }

  int distance = getDistance();
  if (distance <= 20) {
    Stop();
    digitalWrite(RedLED, HIGH);
    digitalWrite(GreenLED, LOW);
    uright();
    delay(2000);
    
    if (lastMovementCommand.startsWith("*go") || lastMovementCommand.startsWith("*long") || lastMovementCommand.startsWith("*Go")) {
      executeCommand(lastMovementCommand);
    }
  } else {
    digitalWrite(RedLED, LOW);
    digitalWrite(GreenLED, (millis() % 10000 < 5000) ? HIGH : LOW);
  }
}

void executeCommand(String cmd) {
  if (cmd == "*forward#" || cmd == "*Forward#") {
    forward();
    lastMovementCommand = cmd;
  } else if (cmd == "*slow move forward#" || cmd == "*Slow move forward#") {
    lforward();
    lastMovementCommand = cmd;
  } else if (cmd == "*spin motor 1#" || cmd == "*spin Motor 1#" || cmd == "*Spin motor 1#") {
    Spin1();
  } else if (cmd == "*spin motor 2#" || cmd == "*spin Motor 2#" || cmd == "*Spin motor 2#") {
    Spin2();
  } else if (cmd == "*spin motor 3#" || cmd == "*spin Motor 3#" || cmd == "*Spin motor 3#") {
    Spin3();
  } else if (cmd == "*spin motor 4#" || cmd == "*spin Motor 4#" || cmd == "*Spin motor 4#") {
    Spin4();
  } else if (cmd == "*long forward#") {
    lforward();
    lastMovementCommand = cmd;
  } else if (cmd == "*slow move backward#" || cmd == "*Slow move backward#") {
    sbackward();
  } else if (cmd == "*move backward#" || cmd == "*backward#" || cmd == "*Move backward#" || cmd == "*Backward#") {
    backward();
  } else if (cmd == "*left#" || cmd == "*turn left#" || cmd == "*Left#" || cmd == "*Turn left#") {
    left();
  } else if (cmd == "*right#" || cmd == "*turn right#" || cmd == "*Right#" || cmd == "*Turn right#") {
    right();
  } else if (cmd == "*right you turn#" || cmd == "*right U turn#" || cmd == "*Right you turn#" || cmd == "*Right U turn#") {
    uright();
  } else if (cmd == "*left you turn#" || cmd == "*left U turn#" || cmd == "*Left you turn#" || cmd == "*Left U turn#") {
    uleft();
  } else if (cmd == "*stop#" || cmd == "*Stop#") {
    Stop();
  }
}

// Motor control functions
void Spin1() { motor1.setSpeed(255); motor1.run(FORWARD); delay(1000); motor1.run(RELEASE); }
void Spin2() { motor2.setSpeed(255); motor2.run(FORWARD); delay(1000); motor2.run(RELEASE); }
void Spin3() { motor3.setSpeed(255); motor3.run(FORWARD); delay(1000); motor3.run(RELEASE); }
void Spin4() { motor4.setSpeed(255); motor4.run(FORWARD); delay(1000); motor4.run(RELEASE); }
void uleft() { motor1.setSpeed(255); motor1.run(FORWARD); motor2.setSpeed(255); motor2.run(BACKWARD); motor3.setSpeed(255); motor3.run(FORWARD); motor4.setSpeed(255); motor4.run(BACKWARD); delay(1000); motor1.run(RELEASE); motor2.run(RELEASE); motor3.run(RELEASE); motor4.run(RELEASE); }
void uright() { motor1.setSpeed(255); motor1.run(BACKWARD); motor2.setSpeed(255); motor2.run(FORWARD); motor3.setSpeed(255); motor3.run(BACKWARD); motor4.setSpeed(255); motor4.run(FORWARD); delay(1000); motor1.run(RELEASE); motor2.run(RELEASE); motor3.run(RELEASE); motor4.run(RELEASE); }
void lforward() { motor1.setSpeed(150); motor1.run(FORWARD); motor2.setSpeed(150); motor2.run(FORWARD); motor3.setSpeed(150); motor3.run(FORWARD); motor4.setSpeed(150); motor4.run(FORWARD); }
void forward() { motor1.setSpeed(255); motor1.run(FORWARD); motor2.setSpeed(255); motor2.run(FORWARD); motor3.setSpeed(255); motor3.run(FORWARD); motor4.setSpeed(255); motor4.run(FORWARD); delay(1000); motor1.run(RELEASE); motor2.run(RELEASE); motor3.run(RELEASE); motor4.run(RELEASE); }
void sbackward() { motor1.setSpeed(150); motor1.run(BACKWARD); motor2.setSpeed(150); motor2.run(BACKWARD); motor3.setSpeed(150); motor3.run(BACKWARD); motor4.setSpeed(150); motor4.run(BACKWARD); delay(1000); motor1.run(RELEASE); motor2.run(RELEASE); motor3.run(RELEASE); motor4.run(RELEASE); }
void backward() { motor1.setSpeed(255); motor1.run(BACKWARD); motor2.setSpeed(255); motor2.run(BACKWARD); motor3.setSpeed(255); motor3.run(BACKWARD); motor4.setSpeed(255); motor4.run(BACKWARD); delay(1000); motor1.run(RELEASE); motor2.run(RELEASE); motor3.run(RELEASE); motor4.run(RELEASE); }
void left() { motor1.setSpeed(255); motor1.run(FORWARD); motor2.setSpeed(255); motor2.run(BACKWARD); motor3.setSpeed(255); motor3.run(FORWARD); motor4.setSpeed(255); motor4.run(BACKWARD); delay(500); motor1.run(RELEASE); motor2.run(RELEASE); motor3.run(RELEASE); motor4.run(RELEASE); }
void right() { motor1.setSpeed(255); motor1.run(BACKWARD); motor2.setSpeed(255); motor2.run(FORWARD); motor3.setSpeed(255); motor3.run(BACKWARD); motor4.setSpeed(255); motor4.run(FORWARD); delay(500); motor1.run(RELEASE); motor2.run(RELEASE); motor3.run(RELEASE); motor4.run(RELEASE); }
void Stop() { motor1.run(RELEASE); motor2.run(RELEASE); motor3.run(RELEASE); motor4.run(RELEASE); }

int getDistance() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(1);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  int duration = pulseIn(Echo, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}
