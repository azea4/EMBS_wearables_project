
/*  Getting_BPM_to_Monitor prints the BPM to the Serial Monitor, using the least lines of code and PulseSensor Library.
 *  Tutorial Webpage: https://pulsesensor.com/pages/getting-advanced
 *
--------Use This Sketch To------------------------------------------
1) Displays user's live and changing BPM, Beats Per Minute, in Arduino's native Serial Monitor.
2) Print: "♥  A HeartBeat Happened !" when a beat is detected, live.
2) Learn about using a PulseSensor Library "Object".
4) Blinks LED on PIN 13 with user's Heartbeat.
--------------------------------------------------------------------*/

#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.  

//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
const int  NUM_READINGS = 10;
int readings[NUM_READINGS];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int averageBPM = 0;                // the average
int initializer = 0;  
                            
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"


void setup() {   

  Serial.begin(9600);          // For Serial Monitor

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }

  for(int thisReading = 0; thisReading <  NUM_READINGS; thisReading ++){
    readings[thisReading] = 0;
  }
  Serial.println("Initializing...");    //FIX ME
}



void loop() {

  int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                                 // "myBPM" hold this BPM value now. 
  
  if(pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
   Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
   Serial.print("BPM: ");                        // Print phrase "BPM: " 
   Serial.println(myBPM);                        // Print the value inside of myBPM.
  
  }
  delay(20);

//  while(initializer < NUM_READINGS && readIndex < NUM_READINGS){
//    initializer++;
//    readings[readIndex] = myBPM;
//    readIndex++;
//  }
//  
//  while(initializer > NUM_READINGS){
//  total = total - readings[readIndex];          //subtract the last reading
//  readings[readIndex] = myBPM;                 //read from PPG
//  total = total + readings[readIndex];        //add the reading to the total
//  readIndex = readIndex + 1;                  //advance to next position in array
//  
//  //if end of array...
//  if(readIndex >= NUM_READINGS){
//  //wrap around to beginning
//    readIndex = 0;
//  }
//  }
  averageBPM = total / NUM_READINGS;
  Serial.print("Average BPM: ");
  Serial.println(averageBPM);
  
  delay(10000);                                   
  

}

  
