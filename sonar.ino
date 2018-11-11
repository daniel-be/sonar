#include <Servo.h>

#define TRIG 4
#define ECHO 2
#define SERVO 3

#define SONIC_SPEED_FACTOR 340
#define MAX_ANGLE 170
#define SONIC_TIMEOUT 3000

Servo servo;
byte angle = 0;
bool up = true;
byte buff[2];

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  servo.attach(SERVO);
  Serial.begin(9600);
}

void loop() {
  if (angle == MAX_ANGLE && up) { up = false; }
  if (angle == 0 && !up) { up = true; }
  servo.write(angle);

  buff[0] = get_distance();
  buff[1] = angle;
  Serial.write(buff, sizeof(buff) / sizeof(byte));
  
  if (up) { angle++; }
  else { angle--; }
  
  delay(100);
}

byte get_distance()
{
  long t = 0;
  
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  noInterrupts();
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  t = pulseIn(ECHO, HIGH, SONIC_TIMEOUT);
  interrupts();

  return ((t / 2) * SONIC_SPEED_FACTOR) / 10000;
}
