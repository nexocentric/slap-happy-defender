

#include <NewPing.h>
#include <PololuMaestro.h>
 
#define TRIGGER_PIN  3  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 300 // Maximum distance we want to ping for (in centimeters).
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int FSR_Pin = A2; //analog pin 2
boolean triggered_s = false; //sonar sensor
 
/* On boards with a hardware serial port available for use, use
that port to communicate with the Maestro. For other boards,
create a SoftwareSerial object using pin 10 to receive (RX) and
pin 11 to transmit (TX). */

#ifdef SERIAL_PORT_HARDWARE_OPEN
  #define maestroSerial SERIAL_PORT_HARDWARE_OPEN
#else
  #include <SoftwareSerial.h>
  SoftwareSerial maestroSerial(10, 11);
#endif

/* Next, create a Maestro object using the serial port.*/
MicroMaestro maestro(maestroSerial);

void setup(){
Serial.begin(9600);
//Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.  
 
}
 
void loop(){

    if(triggered_s == true){
      Serial.println("swinging");
      //swing();
        // Set the target of channel 0 to 1500 us, and wait 2 seconds.
      Serial.println("Sweep1");  
      maestro.setTarget(0, 6000);
      delay(2000);

      // Set the target of channel 0 to 1750 us, and wait 2 seconds.
      Serial.println("Sweep2");
      maestro.setTarget(0, 7000);
      delay(2000);
    
      // Set the target of channel 0 to 1250 us, and wait 2 seconds.
      Serial.println("Sweep3");
      maestro.setTarget(0, 5000);
      delay(2000);
    }
    else{
      delay(50);// Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
      int cm = sonar.ping_cm(); // Send ping, get ping time in centimeters (cm).
      Serial.println(cm);
      if(cm < 50){ 
         triggered_s = true;
      }
   }
   
   int FSRReading = analogRead(FSR_Pin); 
   if (FSRReading > 100){
     Serial.println("stopping");
     triggered_s = false;
     maestro.setTarget(0,0);
     //stop_swing();
   }
}
 
void swing(){
  //maestro.setSpeed(0, 0);
 // maestro.setAcceleration(0, 0);
  /*Serial.println("Sweep1");
  maestro.setTarget(0, 6000);
  delay(200);
  Serial.println("Sweep2");
  maestro.setTarget(0, 100);
  delay(200);*/
  
  // Set the target of channel 0 to 1500 us, and wait 2 seconds.
  Serial.println("Sweep1");  
  maestro.setTarget(0, 6000);
  delay(2000);

  // Set the target of channel 0 to 1750 us, and wait 2 seconds.
  Serial.println("Sweep2");
  maestro.setTarget(0, 7000);
  delay(2000);

  // Set the target of channel 0 to 1250 us, and wait 2 seconds.
  Serial.println("Sweep3");
  maestro.setTarget(0, 5000);
  delay(2000);
}
 
void stop_swing(){
 // maestro.setSpeed(0, 0);
 // maestro.setAcceleration(0, 0);
 // maestro.setTarget(0,0);
   Serial.println("Off");  
  maestro.setTarget(0, 6000);
}
