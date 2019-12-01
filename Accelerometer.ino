#include <OrangutanLCD.h>
#include <OrangutanMotors.h>

#define tiltSensor 5

int tiltSensor_Value;

OrangutanLCD lcd;
OrangutanMotors motors;

void setup() 
{ clear();
}

void loop() 
{
  lcd.gotoXY(0,0);
  tiltSensor_Value = analogRead(tiltSensor);
  lcd.print(tiltSensor_Value);
}
