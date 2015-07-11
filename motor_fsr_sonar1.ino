#include <NewPing.h>
#include "DualMC33926MotorShield.h"

#define TRIGGER_PIN  2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 300 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int FSR_Pin = A2; //analog pin 2

DualMC33926MotorShield md;

void setup() 
{
  Serial.begin(115200);
  md.init();
// turn on motor
//motor2.setSpeed(200);
//motor4.setSpeed(200);
}

void loop() 
{
  int speed =400; // mx speed according to pololu. is this current?
  int FSRReading = analogRead(FSR_Pin); 
  md.setM1Speed(speed);

  if (FSRReading > 100)
  {
     md.setM1Speed(0);
     Serial.println(FSRReading);
     Serial.print(" Stopped ");
     delay(250); //just here to slow down the output for easier reading
   }
 
  delay(50);                // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int cm = sonar.ping_cm(); // Send out the ping, get the results in centimeters.
 // Serial.print("Ping: ");
 // Serial.print(cm);         // Print the result (0 = outside the set distance range, no ping echo)
 // Serial.println("cm");

  if (cm < 50)
   {
      md.setM1Speed(0);
      Serial.print(" Stopped ");
      Serial.print("Ping: ");
      Serial.print(cm);         // Print the result (0 = outside the set distance range, no ping echo)
      Serial.println("cm");
      delay(250); //just here to slow down the output for easier reading
   }
 
}
  
