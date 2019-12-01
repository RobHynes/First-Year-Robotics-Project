#include <OrangutanMotors.h>

OrangutanMotors motors;

void setup() {
  delay(1000);
    motors.setSpeeds(50,-50);
    delay(620);
  motors.setSpeeds(0,0);
}

void loop() {
  // put your main code here, to run repeatedly:

}
