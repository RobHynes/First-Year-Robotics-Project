#include <OrangutanLCD.h>
#include <OrangutanAnalog.h>
#include <OrangutanMotors.h>

#define leftLDR 6
#define rightLDR 7

OrangutanLCD lcd;
OrangutanMotors motors;

int leftLDR_Value;
int rightLDR_Value;
int counter;
int location;
int Sum;
int min_Sum = 9999;

void setup() 
{
  delay(1000);
  for(counter = 0; counter < 51; counter++)
  {
    leftLDR_Value = analogRead(leftLDR);
    rightLDR_Value = analogRead(rightLDR);
    Sum = leftLDR_Value + rightLDR_Value;
    if (Sum < min_Sum)
    {
      location = counter;
      min_Sum = Sum;
    }
    motors.setSpeeds(-50,50);
    delay(25);
    motors.setSpeeds(0,0);
  }
  for(counter = 0; counter < (51-location); counter++)
  {
    motors.setSpeeds(50,-50);
    delay(25);
  }
  
  clear();
  lcd.gotoXY(0,0);
  lcd.print(location);
  motors.setSpeeds(50,50);
  delay(1500);
  motors.setSpeeds(0,0);
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  leftLDR_Value = analogRead(leftLDR);
  rightLDR_Value = analogRead(rightLDR);
  if (leftLDR_Value > rightLDR_Value) // left LDR further from light, turn right
   {
    motors.setSpeeds(50,25);
   }
  else  // right LDR further from light, turn left 
   {
    motors.setSpeeds(25,50);
   }
}
