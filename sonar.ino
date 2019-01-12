#include <Servo.h>
#include <NewPing.h>

#define TRIG 4
#define ECHO 2
#define SERVO 3
#define MAX_ANGLE 180

NewPing sonar(TRIG, ECHO, 50);
Servo servo;
byte angle = 0;
bool up = true;
byte buff[2];

void setup() {
  servo.attach(SERVO);
  Serial.begin(115200);
}

void loop() {
  if (angle == MAX_ANGLE && up) { up = false; }
  if (angle == 0 && !up) { up = true; }
  servo.write(angle);

  buff[0] = sonar.ping_cm();
  buff[1] = angle;
  Serial.write(buff, sizeof(buff) / sizeof(byte));
  
  if (up) { angle++; }
  else { angle--; }
  
  delay(100);
}
