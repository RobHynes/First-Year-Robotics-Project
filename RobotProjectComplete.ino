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

void setup() // Light Follower Setup
{
 
  OrangutanBuzzer::playFromProgramSpace(welcome);
  delay(500);
  calibrateAccel();  // call accelerometer calibration function  
//  lightFollower();   // call light follower function
  counter = 0;
  clear();           
  lcd.gotoXY(0,0);
  lcd.print(1);      // temporary check to show return to setup after light follower
//  _180turn();        // call 180 turn function so robot faces right direction on line
  clear();           
  lcd.gotoXY(0,0);
  lcd.print(2);      // temporary check to show return to setup after 180
  delay(500);
                     // line follower
  robot.init(2000,1);
   
  for (counter = 0; counter < 80; counter++)
  {
    if (counter <20 || counter >= 60)
      motors.setSpeeds(40,-40); 
    else
      motors.setSpeeds(-40,40);

      robot.calibrateLineSensors(IR_EMITTERS_ON);
      delay(20);  // counter counts to 80, delay of 20 each time = 1600 ms
  }
  motors.setSpeeds(0,0);
  
  counter = 0;

  delay(1000); //delay to allow accelerometer to settle
  tiltSensor_Value = analogRead(tiltSensor);
  
  while(tiltSensor_Value < 342)
  {
    unsigned int position = robot.readLine(sensors, IR_EMITTERS_ON);
   
    if(position < 1000) // turn left to  stay on line
      motors.setSpeeds(10,35);

    else if(position > 3000) // turn right to stay on line
      motors.setSpeeds(35,10);

    else // drive straight
      motors.setSpeeds(35,35);

    delay(100);
    tiltSensor_Value = analogRead(tiltSensor);
    clear();           
    lcd.gotoXY(0,0);
    lcd.print(tiltSensor_Value);

    delay(10);
  }
  
  motors.setSpeeds(0,0);
  clear();
}

void loop() 
{
}

void _180turn()
{
  delay(1000);
  motors.setSpeeds(50,-50);
  delay(620);
  motors.setSpeeds(0,0);
}

void lightFollower()
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

   motors.setSpeeds(0,0);
   clear();
   lcd.gotoXY(0,0);
   lcd.print(location);
   motors.setSpeeds(50,50);
   delay(1500);
   motors.setSpeeds(0,0);
   
  while(leftLDR_Value > 75 && rightLDR_Value > 75)
  {
    leftLDR_Value = analogRead(leftLDR);
    rightLDR_Value = analogRead(rightLDR);
  
    if (leftLDR_Value > rightLDR_Value) // left LDR further from light, turn right
      motors.setSpeeds(50,25);
    else  // right LDR further from light, turn left
      motors.setSpeeds(25,50);
  }
  motors.setSpeeds(0,0);
}

void lineFollower()
{
   for (counter = 0; counter < 80; counter++)
   {
      if (counter <20 || counter >= 60)
        motors.setSpeeds(40,-40); 
      else
        motors.setSpeeds(-40,40);

      robot.calibrateLineSensors(IR_EMITTERS_ON);
      delay(20);  // counter counts to 80, delay of 20 each time = 1600 ms
   }
   motors.setSpeeds(0,0);

   while(1)
   {
    unsigned int position = robot.readLine(sensors, IR_EMITTERS_ON);
    for(counter = 0; counter < 10001; counter++)
    {
     if(counter > 600)
     {
      tiltSensor_Value = analogRead(tiltSensor);
     }
    }
        
    if(position < 1000) // turn left to  stay on line
    motors.setSpeeds(0,70);

    else if(position > 3000) // turn right to stay on line
    motors.setSpeeds(70,0);

    else // drive straight
    motors.setSpeeds(70,70);
   } 
}

void seesawBalance()
{
  OrangutanBuzzer::playFromProgramSpace(welcome);
  
  tiltSensor_Value = analogRead(tiltSensor);
  if (tiltSensor_Value > 341)
  {
    motors.setSpeeds(40,40);
    delay(10);
  }
  else if (tiltSensor_Value < 335)
  {
    motors.setSpeeds(-40,-40);
    delay(10);
  }
  else
  {
    motors.setSpeeds(0,0);
  }
}

void calibrateAccel()
{
  tiltSensor_Value = analogRead(tiltSensor);
  horizontal = tiltSensor_Value;
  clear();
  lcd.gotoXY(0,0);
  lcd.print(horizontal);
  delay(500);
}
