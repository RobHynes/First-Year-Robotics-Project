#include <OrangutanLCD.h>
#include <OrangutanAnalog.h>

#define tiltSensor 5

OrangutanLCD lcd;

int tiltSensor_Value; // Accelerometer calibration variables
int horizontal;

void setup() {
  // put your setup code here, to run once:
tiltSensor_Value = analogRead(tiltSensor);
  horizontal = tiltSensor_Value;
  clear();
  lcd.gotoXY(0,0);
  lcd.print(horizontal);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
