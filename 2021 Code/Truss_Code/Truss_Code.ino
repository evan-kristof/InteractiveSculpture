/* Interactive Sculpture Truss Code
 * This file contains the main functions to exectue the code. [Setup Arduino -> setup() function, Loop code -> loop() function]
 * Pin values are declared in the config.h folder. If you wish to modify the pins/circuitry, ensure you update the values in the config.h file for the code to work properly
 * 
 * Truss_Code.ino
 * 
 * DATE CREAED: 1/29/21 BY OMAR WAKED
 * DATE MODIFIED: 1/29/21 BY OMAR WAKED
 * IMPORTANT: UPDATE THE MODIFIED DATE AND NAME ABOVE 
 * LINK TO CODE ON GITHUB: https://github.com/OmarWaked/InteractiveSculpture.git
*/

//IMPORT FILES REQUIRED FOR CODE IN THIS FILE TO WORK
#include "HX711.h"
#include "config.h"

//DEFINE VARIABLES
HX711 load_cell (LOADCELL_DT_PIN, LOADCELL_SCK_PIN); //HX711 LOAD CELL


//THIS FUNCTION WILL RUN ONCE WHEN THE ARDUINO IS POWERED UP
void setup() {
    Serial.begin(9600);                              //START SERIAL MONITOR
    //delay(50);                                       //50 MILLISECOND DELAY
    
    pinMode(RED_LED, OUTPUT);                        //Output for the LED lights
    pinMode(GREEN_LED, OUTPUT);                      //Output for the LED lights
    pinMode(BLUE_LED, OUTPUT);                       //Output for the LED lights
    
    Serial.println("Before setting up the scale:");
    Serial.print("read: \t\t");
    Serial.println(load_cell.read());                // print a raw reading from the ADC for scale 1
    Serial.print("read average: \t\t");
    Serial.println(load_cell.read_average(5));      // print the average of 5 readings from the ADC for scale 1
    Serial.println("test");
    Serial.print("get value: \t\t");
    Serial.println(load_cell.get_value(5));          // print the average of 5 readings from the ADC minus the tare weight (not set yet) for scale 1
  
    Serial.print("get units: \t\t");
    Serial.println(load_cell.get_units(5),1);       // print the average of 5 readings from the ADC minus tare weight for scale 1
    
    load_cell.set_scale(2280.f);                     // this value is obtained by calibrating the scale with known weights; see the README for details
    load_cell.tare();                                // reset the scale to 0 for scale 1
    Serial.println("After setting up the scale:");
  
    Serial.print("read: \t\t");
    Serial.println(load_cell.read());                // print a raw reading from the ADC for scale 1
  
    Serial.print("read average: \t\t");
    Serial.println(load_cell.read_average(20));      // print the average of 20 readings from the ADC for scale 1
    //delay(1000);
  
    Serial.print("get value: \t\t");
    Serial.println(load_cell.get_value(5));          // print the average of 5 readings from the ADC minus the tare weight, set with tare() for scale 1
  
    Serial.print("get units: \t\t");
    Serial.println(load_cell.get_units(5), 1);       // print the average of 5 readings from the ADC minus tare weight, divided by scale parameter wit set_scale
    Serial.println("Readings:");                     //Serial monitor readings
  
    //delay(1000);                                     //Delay in serialprint reading of 500 milliseconds
}

int CAL_FACT = -7050;
int MIN_LB = -10;
int MAX_LB = 10;
int MAP_LOW = 30;
int NEG_FLR = -1; // Negative floor, minimum amount of force before led will activate for tension
int POS_FLR = 1;  // Positive floor, minimum amount of force before led will activate for compression



//THIS FUNCTION WILL RUN FOREVER UNLESS INSTRUCTED TO STOP
void loop() {
    load_cell.set_scale(CAL_FACT);         //Adjust to this calibration factor for scale 1
    Serial.print("sensor readings:\t");
    Serial.print(load_cell.get_units(), 1);  
    Serial.print("      ");
    Serial.print("\t| average:\t");
    Serial.println(load_cell.get_units(10), 1);
     //delay(1000);
  
    int ledbrightness;                               //Integer for the brightness of the LED lights      
    float cell = load_cell.get_units(5);
    
    if (cell < NEG_FLR){     // testing for tension in load cell
      ledbrightness = ((map(cell, MIN_LB, 0, MAP_LOW, 255))*-1); //Convert the reading from the scale into a pwm output
      analogWrite(GREEN_LED, ledbrightness);
      analogWrite(RED_LED, 0);
    }else if (cell > POS_FLR){     //testing for compression in load cell
      analogWrite(GREEN_LED, 0);
      ledbrightness = map(cell, 0, MAX_LB, MAP_LOW, 255);
      analogWrite(RED_LED, ledbrightness);
    }else if (NEG_FLR <= cell <= POS_FLR){
      analogWrite(GREEN_LED, 0);
      analogWrite(RED_LED, 0);
      //Serial.println("no load detected sensor 1");
    }
}


/* LIBRARIES USED & TUTORIALS
 * 
 *  HX711: https://www.arduino.cc/reference/en/libraries/hx711-arduino-library/
 *  LOAD CELL AMPLIFIER HX711: https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all
 * 
*/
