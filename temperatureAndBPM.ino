int(tempPin) = A5;

#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"



void setup() {
  // put your setup code here, to run once:

  //communicate with computer
  Serial.begin(115200);

  //temperature sensor
  pinMode(tempPin, INPUT);
  
  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  } 
}

void loop() {
  // put your main code here, to run repeatedly:

  
  //calculate temperature
   float voltage = analogRead(tempPin) * (5.0/1024.0);     //5 volts divided by 
   float degreesC = (voltage - 0.5) * 100.0;               //voltage to temperature (degrees Celsius)
   //degreesC += 6;                                          //we don't know how to calibrate lol
   float degreesF = degreesC * (9.0/5.0) + 32.0;           //degrees Celsius to degrees Farnheit

  
  
   Serial.print("Temperature (F): ");
   Serial.println( degreesF);

   Serial.print("Temperature (C): ");
   Serial.println(degreesC);

   delay(1000); 

     // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.setThreshold(Threshold);   




 int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 

if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
 Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 Serial.print("BPM: ");                        // Print phrase "BPM: " 
 Serial.println(myBPM);                        // Print the value inside of myBPM. 


//int averageBPM;
//int sumBPM = 0;
//int BPMcount = 0;
//int ellapsedTime = millis();
//int timeAfter = 10000;
//
//  while((ellapsedTime) % timeAfter == 0){     //FIX ME!!!!
//  sumBPM += myBPM; 
//  BPMcount += 1;
//  Serial.println("ACK!");
//
//  averageBPM = sumBPM / BPMcount;
  } 




Serial.print("Average BPM: ");
Serial.println(averageBPM);

  delay(20);                    // considered best practice in a simple sketch.

}
}
