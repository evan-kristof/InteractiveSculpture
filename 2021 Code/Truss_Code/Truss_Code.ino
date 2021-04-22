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
HX711 load_cella(LOADCELLa_DT_PIN, LOADCELLa_SCK_PIN); //HX711 LOAD CELL a
//HX711 load_cellb(LOADCELLb_DT_PIN, LOADCELLb_SCK_PIN); //HX711 LOAD CELL b
//HX711 load_cellc(LOADCELLc_DT_PIN, LOADCELLc_SCK_PIN); //HX711 LOAD CELL c

// THE 'start' FUNCTION STARTS COMMUNICATION WITH THE LOAD CELLS AND LEDs. IT RUNS ONCE FOR
// EACH LOAD CELL AND IS INITIATED BY THE 'setup' FUNCTION.
 
void start(HX711 lc) {
    Serial.begin(9600);                              //START SERIAL MONITOR
    
    pinMode(RED_LED, OUTPUT);                        //Output for the LED lights
    pinMode(GREEN_LED, OUTPUT);                      //Output for the LED lights
    pinMode(BLUE_LED, OUTPUT);                       //Output for the LED lights
    
    Serial.println("Before setting up the scale:");
    Serial.print("read: \t\t");
    Serial.println(lc.read());                // print a raw reading from the ADC 
    Serial.print("read average: \t\t");
    Serial.println(lc.read_average(5));       // print the average of 5 readings from the ADC 
    Serial.println("test");
    Serial.print("get value: \t\t");
    Serial.println(lc.get_value(5));          // print the average of 5 readings from the ADC minus the tare weight (not set yet)
  
    Serial.print("get units: \t\t");
    Serial.println(lc.get_units(5));       // print the average of 5 readings from the ADC minus tare weight 
    
    lc.set_scale(2280.f);                     // this value is obtained by calibrating the scale with known weights; see the README for details
    lc.tare();                                // reset the scale to 0 for scale 1
    
    Serial.println("After setting up the scale:");
  
    Serial.print("read: \t\t");
    Serial.println(lc.read());                // print a raw reading from the ADC for scale 1
  
    Serial.print("read average: \t\t");
    Serial.println(lc.read_average(5));      // print the average of 20 readings from the ADC for scale 1
    
    Serial.print("get value: \t\t");
    Serial.println(lc.get_value(5), 1);          // print the average of 5 readings from the ADC minus the tare weight, set with tare()
  
    Serial.print("get units: \t\t");
    Serial.println(lc.get_units(5), 1);       // print the average of 5 readings from the ADC minus tare weight, divided by scale parameter wit set_scale
    Serial.println("Readings:");              //Serial monitor readings
}

void set_calibration(HX711 lc){
    lc.set_scale(CALIBRATION_FACTOR);         //Adjust to this calibration factor for scale 1
    Serial.print("sensor readings:\t");
    Serial.print(lc.get_units(), 1);  
    Serial.print("      ");
    Serial.print("\t| average:\t");
    Serial.println(lc.get_units(10), 1);
    Serial.println();
    Serial.println();  
}

// THE 'setup' FUNCTION WILL RUN ONCE WHEN THE ARDUINO IS POWERED UP. IT IS A REQUIRED PART OF 
// ALL ARDUINO SKETCHES. IN THIS CASE IT RUNS THE 'start' AND 'set_calibration' FUNCTIONS FOR
// EACH LOAD CELL IN THE TRUSS SCULPTURE.
 
void setup() {
    start(load_cella);
    //start(load_cellb);
    //start(load_cellc);

    set_calibration(load_cella);
    //set_calibration(load_cellb);
    //set_calibration(load_cellc);
}

// THE 'read_send' FUNCTION READS THE INPUT FROM THE LOAD CELL AND DECIDES WHETHER OR NOT 
// IT IS IN TENSION, COMPRESSION, OR NEITHER. THEN IT LIGHTS THE APPROPRIATE LED, OR DOES
// NOTHING AND STARTS OVER TO CHECK THE LOAD CELL AGAIN. THIS FUNCTION IS INIATED BY THE
// 'loop' FUNCTION AND THEREFORE RUNS CONINTUOUSLY AS LONG THE ARDUINO IS POWERED ON. 

    
void read_send(HX711 lc){
    
    int ledbrightness;                               //Integer for the brightness of the LED lights      

    if (lc.get_units() < NEGATIVE_FLOOR){     // testing if sensor 1 is in tension
      ledbrightness = ((map(lc.get_units(), MIN_LB, 0, MAP_LOW, 255))*-1); //Convert the reading from the scale into a pwm output
      analogWrite(GREEN_LED, ledbrightness);
      analogWrite(RED_LED, 0);
      Serial.print("compression1");
      Serial.print("      ");
      Serial.print(ledbrightness);
      Serial.println();
    }else if (lc.get_units() > POSITIVE_FLOOR){     //testing for compression in sensor 1
      ledbrightness = map(lc.get_units(), 0, MAX_LB, MAP_LOW, 255);
      analogWrite(RED_LED, ledbrightness);
      analogWrite(GREEN_LED, 0);
      Serial.print("tension1");
      Serial.print("      ");
      Serial.print(ledbrightness);
      Serial.println(); 
    }else if (NEGATIVE_FLOOR <= lc.get_units() <= POSITIVE_FLOOR){
      analogWrite(GREEN_LED, 0);
      analogWrite(RED_LED, 0);
      Serial.println("no load detected sensor 1");
    }
}

// THE 'loop' FUNCTION WILL RUN FOREVER UNLESS INSTRUCTED TO STOP. IT IS A REQUIRED PART OF 
// ALL ARDUINO SKETCHES. IT CHECKS EACH LOAD CELL FOR TENSION AND COMPRESSION CONSECUTIVELY.

void loop() {
    read_send(load_cella);
    //read_send(load_cellb);
    //read_send(load_cellc);
}
/* LIBRARIES USED & TUTORIALS
 * 
 *  HX711: https://www.arduino.cc/reference/en/libraries/hx711-arduino-library/
 *  LOAD CELL AMPLIFIER HX711: https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all
 * 
*/
