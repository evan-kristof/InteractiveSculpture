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
HX711 load_cella (LOADCELLa_DT_PIN, LOADCELLa_SCK_PIN); //HX711 LOAD CELL a
HX711 load_cellb (LOADCELLb_DT_PIN, LOADCELLb_SCK_PIN); //HX711 LOAD CELL b
HX711 load_cellc (LOADCELLc_DT_PIN, LOADCELLc_SCK_PIN); //HX711 LOAD CELL c


void setup_function(HX711 lc) {
    Serial.begin(9600);                              //START SERIAL MONITOR
    
    pinMode(RED_LED, OUTPUT);                        //Output for the LED lights
    pinMode(GREEN_LED, OUTPUT);                      //Output for the LED lights
    pinMode(BLUE_LED, OUTPUT);                       //Output for the LED lights
    
    Serial.println("Before setting up the scale:");
    Serial.print("read: \t\t");
    Serial.println(lc.read());                // print a raw reading from the ADC for scale 1
    Serial.print("read average: \t\t");
    Serial.println(lc.read_average(5));       // print the average of 5 readings from the ADC for scale 1
    Serial.println("test");
    Serial.print("get value: \t\t");
    Serial.println(lc.get_value(5));          // print the average of 5 readings from the ADC minus the tare weight (not set yet) for scale 1
  
    Serial.print("get units: \t\t");
    Serial.println(lc.get_units(5), 1);       // print the average of 5 readings from the ADC minus tare weight for scale 1
    
    lc.set_scale(2280.f);                     // this value is obtained by calibrating the scale with known weights; see the README for details
    lc.tare();                                // reset the scale to 0 for scale 1
    
    Serial.println("After setting up the scale:");
  
    Serial.print("read: \t\t");
    Serial.println(lc.read());                // print a raw reading from the ADC for scale 1
  
    Serial.print("read average: \t\t");
    Serial.println(lc.read_average(20));      // print the average of 20 readings from the ADC for scale 1
    
    Serial.print("get value: \t\t");
    Serial.println(lc.get_value(5));          // print the average of 5 readings from the ADC minus the tare weight, set with tare() for scale 1
  
    Serial.print("get units: \t\t");
    Serial.println(lc.get_units(5), 1);       // print the average of 5 readings from the ADC minus tare weight, divided by scale parameter wit set_scale
    Serial.println("Readings:");              //Serial monitor readings
}

//THIS FUNCTION WILL RUN ONCE WHEN THE ARDUINO IS POWERED UP
void setup() {
    setup_function(load_cella);
    setup_function(load_cellb);
    setup_function(load_cellc);
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
      delay(DELAY);
    }else if (lc.get_units() > POSITIVE_FLOOR){     //testing for compression in sensor 1
      analogWrite(GREEN_LED, 0);
      ledbrightness = map(lc.get_units(), 0, MAX_LB, MAP_LOW, 255);
      analogWrite(RED_LED, ledbrightness);
      Serial.print("tension1");
      Serial.print("      ");
      Serial.print(ledbrightness);
      Serial.println(); 
      delay(DELAY);
    }else if (NEGATIVE_FLOOR <= lc.get_units() <= POSITIVE_FLOOR){
      analogWrite(GREEN_LED, 0);
      analogWrite(RED_LED, 0);
      Serial.println("no load detected sensor 1");
      delay(DELAY);
    }
}

//THIS FUNCTION WILL RUN FOREVER UNLESS INSTRUCTED TO STOP

void loop() {
    set_calibration(load_cella);
    set_calibration(load_cellb);
    set_calibration(load_cellc);

    read_send(load_cella);
    read_send(load_cellb);
    read_send(load_cellc);
    }
/* LIBRARIES USED & TUTORIALS
 * 
 *  HX711: https://www.arduino.cc/reference/en/libraries/hx711-arduino-library/
 *  LOAD CELL AMPLIFIER HX711: https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all
 * 
*/
