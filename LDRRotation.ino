#include <OrangutanLCD.h>
#include <OrangutanAnalog.h>
#include <OrangutanMotors.h>

#define leftLDR 6
#define rightLDR 7

OrangutanLCD lcd;
OrangutanMotors motors;

int leftLDR_Value;
int rightLDR_Value;
int Sum;
int old_Sum = 9999;

void setup() {
  delay(1000);
  leftLDR_Value = analogRead(leftLDR);
  rightLDR_Value = analogRead(rightLDR);
  old_Sum = leftLDR_Value + rightLDR_Value;
  motors.setSpeeds(-50,50);
  delay(25);
  motors.setSpeeds(0,0);
  leftLDR_Value = analogRead(leftLDR);
  rightLDR_Value = analogRead(rightLDR);
  Sum = leftLDR_Value + rightLDR_Value;
  while(Sum > 1200)
  {
    while(Sum < old_Sum)
    {
      old_Sum = Sum;
      motors.setSpeeds(-50,50);
      delay(25);
      motors.setSpeeds(0,0);
      leftLDR_Value = analogRead(leftLDR);
      rightLDR_Value = analogRead(rightLDR);
      Sum = leftLDR_Value + rightLDR_Value;
    }
    old_Sum = Sum;
  }
  clear();
  lcd.gotoXY(0,0);
  lcd.print(Sum);
  lcd.gotoXY(0,1);
  lcd.print(old_Sum);
}

void loop() {
  // put your main code here, to run repeatedly:

}
