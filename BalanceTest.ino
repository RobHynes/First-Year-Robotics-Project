#include <OrangutanLCD.h>
#include <OrangutanAnalog.h>
#include <OrangutanMotors.h>
#include <PololuQTRSensors.h>     
#include <Pololu3pi.h>
#include <OrangutanBuzzer.h>

#define tiltSensor 5
#define leftLDR 6
#define rightLDR 7

const char welcome[] PROGMEM = ">g32>>c32";

OrangutanLCD lcd;
OrangutanMotors motors;
Pololu3pi robot;
Pololu3pi position;

int tiltSensor_Value; // Accelerometer calibration variables
int horizontal;

int leftLDR_Value;    // Light Follower variables
int rightLDR_Value;
int counter;
int location;
int Sum;
int min_Sum = 9999;

unsigned int sensors[5]; // Line follower sensor array
int tiltAv1 = 335;
int tiltAv2 = 335;
int tiltAv3 = 335;
int tiltAv4 = 335;
int tiltAv5 = 335;
int tiltAverage;
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
tiltSensor_Value = analogRead(tiltSensor);
  if (tiltSensor_Value > 340)
  {
    motors.setSpeeds(40,40);
    delay(10);
    motors.setSpeeds(0,0);
    delay(10);
  }
  else if (tiltSensor_Value < 335)
  {
    motors.setSpeeds(-30,-30);
    delay(10);
    motors.setSpeeds(0,0);
    delay(10);
  }
  else
  {
    motors.setSpeeds(0,0);
    delay(10);
  }
  while(tiltSensor_Value == 336)
  {
    motors.setSpeeds(0,0);
    delay(1000);
  }
}
