#include <OrangutanLCD.h>
#include <OrangutanAnalog.h>
#include <OrangutanMotors.h>

#define leftLDR 6
#define rightLDR 7

OrangutanLCD lcd;
OrangutanMotors motors;

int leftLDR_Value;
int rightLDR_Value;

void setup()
{
}

void loop()
{
  clear();
  lcd.gotoXY(0,0);
  leftLDR_Value = analogRead(leftLDR);
  lcd.print(leftLDR_Value);
  lcd.gotoXY(0,1);
  rightLDR_Value = analogRead(rightLDR);
  lcd.print(rightLDR_Value);
  delay(1000);
}
