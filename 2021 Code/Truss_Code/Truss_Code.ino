/* Interactive Sculpture Truss Code
 * This file contains the main functions to exectue the code. [Setup Arduino -> setup() function, Loop code -> loop() function]
 * Pin values are declared in the config.h folder. If you wish to modify the pins/circuitry, ensure you update the values in the config.h file for the code to work properly
 * 
 * Truss_Code.ino
 * 
 * DATE CREAED: 1/29/21 BY OMAR WAKED
 * DATE MODIFIED: 5/18/21 BY Evan Snow
 * IMPORTANT: UPDATE THE MODIFIED DATE AND NAME ABOVE 
 * LINK TO CODE ON GITHUB: https://github.com/OmarWaked/InteractiveSculpture.git
*/

//IMPORT FILES REQUIRED FOR CODE IN THIS FILE TO WORK
#include "HX711.h"
#include "config.h"
#include <LiquidCrystal.h>

//DEFINE VARIABLES
//load cells

HX711 load_cell1 (LOADCELL_DT_PIN1, LOADCELL_SCK_PIN1);
//HX711 load_cell2 (LOADCELL_DT_PIN2, LOADCELL_SCK_PIN2);
//HX711 load_cell3 (LOADCELL_DT_PIN3, LOADCELL_SCK_PIN3);

//HX711 LOAD CELL CALIBRATION FACTOR 
float SCALE = 19270.0; // for the larger S-type load cell SCALE should be about 19470, for smaller round load cell SCALE should be about 27470

//LCD pins
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//THIS FUNCTION WILL RUN ONCE WHEN THE ARDUINO IS POWERED UP

void setup() {
    Serial.begin(9600);                              //START SERIAL MONITOR
    pinMode(RED_LED, OUTPUT);                        //Output for the LED lights
    pinMode(GREEN_LED, OUTPUT);                      //Output for the LED lights
    pinMode(BLUE_LED, OUTPUT);                       //Output for the LED lights
    setupCell(load_cell1);
    load_cell1.tare();                               // reset the scale to 0 for scale 1

    lcd.begin(16, 2);                                // set up the LCD's number of columns and rows:
    lcd.print("hi there :)");                      // Print a message to the LCD.
    delay(4000);
    lcd.clear();
    }

//THIS FUNCTION WILL RUN FOREVER UNLESS INSTRUCTED TO STOP
// the loop function first checks if the calibration button is being pushed. if yes, it runs the set_calibration function which sets a new scale factor.
// if the button is not being pushed it moves on to the read_send function which is the primary part of the loop function.

void loop() {
    if (digitalRead(buttonPin) == HIGH)
    {
     set_calibration(load_cell1);
      //set_calibration(load_cell2);
      //set_calibration(load_cell3);
    }
    read_send(load_cell1);
    //read_send(load_cell2);
    //read_send(load_cell3);
    }

// Functions below here are subsidiary to the above setup() and loop() functions


//intialize load cells. this function is not required for operation of the load cell, it just prints out some basic info to make sure the arduino is communicating with the load cell 
//the numbers printed out are raw data from the load cell, not converted to lbs
void setupCell(HX711 load_cellX){
    load_cellX.set_scale(SCALE);
    Serial.println("test after calibration:");
    Serial.print("read: \t\t");
    Serial.println(load_cellX.read());                // print a raw reading from the ADC for scale 1
    Serial.print("read average: \t\t");
    Serial.println(load_cellX.read_average(5));      // print the average of 20 readings from the ADC for scale 1
    Serial.print("get value: \t\t");
    Serial.println(load_cellX.get_value(5));          // print the average of 5 readings from the ADC minus the tare weight, set with tare() for scale 1
    Serial.print("get units: \t\t");
    Serial.println(load_cellX.get_units(5));       // print the average of 5 readings from the ADC minus tare weight, divided by scale parameter wit set_scale
    }

//read inputs from load cell and control LEDs accordinly 
//this is the code that is continuously looping and checking for tension and compression in the load cell. it does not run unless it is called by the loop function, which in this case it is always being called by the loop function
void read_send(HX711 load_cellX){
    load_cellX.set_scale(SCALE);   // this value is obtained by calibrating the scale with known weights; see the README for details
    int ledbrightness;             //Integer for the brightness of the LED lights    
    float forceC;
    float forceT;
    unsigned long lastUpdate = 0; //passive delay (keeps track of elapsed time)
    if (load_cellX.get_units() < NEGATIVE_FLOOR){     // testing for compression in sensor
      ledbrightness = load_cellX.get_units()*255/MAX_LB; // ledbrightness = (get_units - in_min[0])*(225 - out_min[0]) / (in_max - in_min[0]) + out_min[0]
      forceC = load_cellX.get_units();
      analogWrite(GREEN_LED, ledbrightness);
      analogWrite(RED_LED, 0);
      Serial.print("compression1: ");
      Serial.print(forceC);
      Serial.println(" lbs");
      Serial.print("LED output: ");
      Serial.print(ledbrightness);
      Serial.println(); 
    }else if (load_cellX.get_units() > POSITIVE_FLOOR){     //testing for tension in sensor 1
      ledbrightness = load_cellX.get_units()*255/MAX_LB; // ledbrightness = (get_units - in_min[0])*(225 - out_min[0]) / (in_max - in_min[0]) + out_min[0]
      forceT = load_cellX.get_units();
      analogWrite(RED_LED, ledbrightness);
      analogWrite(GREEN_LED, 0);
      Serial.print("tension1: ");
      Serial.print(forceT);
      Serial.println(" lbs");
      Serial.print("LED output: ");
      Serial.print(ledbrightness);
      Serial.println(); 
    }else if (NEGATIVE_FLOOR <= load_cellX.get_units() <= POSITIVE_FLOOR){
      analogWrite(GREEN_LED, 0);
      analogWrite(RED_LED, 0);
      Serial.println("no load detected sensor 1");
    }
   if(millis() - lastUpdate >= passiveDelayTime){ //Check if timer is equal to or later than the collection time variable in config.h (in milliseconds)
    lastUpdate = millis(); //update old_time to current millis()
    if (load_cellX.get_units()<NEGATIVE_FLOOR){
      lcd.print("compression");
      lcd.setCursor(0,1);
      lcd.print(load_cellX.get_units());
      lcd.setCursor(6,1);
      lcd.print("lbs");
    }else if (load_cellX.get_units()>POSITIVE_FLOOR){
      lcd.print("tension");
      lcd.setCursor(0,1);
      lcd.print(load_cellX.get_units());
      lcd.setCursor(6,1);
      lcd.print("lbs");
    }else if (NEGATIVE_FLOOR <= load_cellX.get_units() <= POSITIVE_FLOOR){
      lcd.print("no load detected");
    }
    //lcd.print(load_cellX.get_units());
    delay(300);
    lcd.clear();
    
    }
    }

//set_calibration is called by the loop function when the calibration button is pushed.
//massReading is the scaled output of the load in pounds
//INT_FORCE is the expeceted force in pounds. this varies depending on the configuration of the truss (equilateral triangle or 45, 45, 90 triangle or 30, 60, 90 triangle)
//CONFIG_FACTOR is set in config.h and is specific to what type of triangle the truss is arranged in
   
void set_calibration(HX711 load_cellX){                         //Refer to this link for the code: https://www.instructables.com/Arduino-Scale-With-5kg-Load-Cell-and-HX711-Amplifi/
   float massReading;
   float INT_FORCE;
   load_cellX.set_scale(SCALE);
   massReading = load_cellX.get_units();
   INT_FORCE = KNOWN_WEIGHT / CONFIG_FACTOR;
   Serial.println(massReading);                                    
   if ((INT_FORCE-0.05 <= massReading <= INT_FORCE+0.05) || (-0.05 <= massReading <= 0.05))
   {
    Serial.println("no calibration needed");
    lcd.print("no calibration needed");
   }
   else if (massReading < INT_FORCE-0.05 || massReading > INT_FORCE+0.05){
    SCALE = load_cellX.get_value() / INT_FORCE;
    Serial.println("calibration complete");
    lcd.print("calibration complete");
   }
   }



/* LIBRARIES USED & TUTORIALS
 * 
 *  HX711: https://www.arduino.cc/reference/en/libraries/hx711-arduino-library/
 *  LOAD CELL AMPLIFIER HX711: https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all
 * 
*/
