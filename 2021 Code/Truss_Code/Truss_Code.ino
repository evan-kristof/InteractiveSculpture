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
//load cells
HX711 load_cell1 (LOADCELL_DT_PIN1, LOADCELL_SCK_PIN1);
HX711 load_cell2 (LOADCELL_DT_PIN2, LOADCELL_SCK_PIN2);
HX711 load_cell3 (LOADCELL_DT_PIN3, LOADCELL_SCK_PIN3);
//other variables
unsigned long lastUpdate = 0; //passive delay (keeps track of elapsed time)
int buttonState = 0;   // variable for reading the pushbutton status (0 = button not pressed, 1 = button pressed)


//THIS FUNCTION WILL RUN ONCE WHEN THE ARDUINO IS POWERED UP
void setup() {
    Serial.begin(9600);                              //START SERIAL MONITOR
    //delay(50);                                       //50 MILLISECOND DELAY
    
    pinMode(RED_LED, OUTPUT);                        //Output for the LED lights
    pinMode(GREEN_LED, OUTPUT);                      //Output for the LED lights
    pinMode(BLUE_LED, OUTPUT);                       //Output for the LED lights
    
    Serial.println("Before setting up the scale:");
    Serial.print("read: \t\t");
    Serial.println(load_cell1.read());                // print a raw reading from the ADC for scale 1
    Serial.print("read average: \t\t");
    Serial.println(load_cell1.read_average(5));       // print the average of 5 readings from the ADC for scale 1
    Serial.println("test");
    Serial.print("get value: \t\t");
    Serial.println(load_cell1.get_value(5));          // print the average of 5 readings from the ADC minus the tare weight (not set yet) for scale 1
  
    Serial.print("get units: \t\t");
    Serial.println(load_cell1.get_units(5), 1);       // print the average of 5 readings from the ADC minus tare weight for scale 1
    
    load_cell1.set_scale(2280.f);                     // this value is obtained by calibrating the scale with known weights; see the README for details
    load_cell1.tare();                                // reset the scale to 0 for scale 1
    Serial.println("After setting up the scale:");
  
    Serial.print("read: \t\t");
    Serial.println(load_cell1.read());                // print a raw reading from the ADC for scale 1
  
    Serial.print("read average: \t\t");
    Serial.println(load_cell1.read_average(20));      // print the average of 20 readings from the ADC for scale 1

    Serial.print("get value: \t\t");
    Serial.println(load_cell1.get_value(5));          // print the average of 5 readings from the ADC minus the tare weight, set with tare() for scale 1
  
    Serial.print("get units: \t\t");
    Serial.println(load_cell1.get_units(5), 1);       // print the average of 5 readings from the ADC minus tare weight, divided by scale parameter wit set_scale
    Serial.println("Readings:");                     //Serial monitor readings
}


//THIS FUNCTION WILL RUN FOREVER UNLESS INSTRUCTED TO STOP
void loop() {
    read_send(load_cell1);
}

//intialize load cells 
void setupCell(HX711 load_cellX){
    Serial.println("Before setting up the scale:");
    Serial.print("read: \t\t");
    Serial.println(load_cellX.read());                // print a raw reading from the ADC for scale 1
    Serial.print("read average: \t\t");
    Serial.println(load_cellX.read_average(5));       // print the average of 5 readings from the ADC for scale 1
    Serial.println("test");
    Serial.print("get value: \t\t");
    Serial.println(load_cellX.get_value(5));          // print the average of 5 readings from the ADC minus the tare weight (not set yet) for scale 1
  
    Serial.print("get units: \t\t");
    Serial.println(load_cellX.get_units(5), 1);       // print the average of 5 readings from the ADC minus tare weight for scale 1
    
    load_cellX.set_scale(2280.f);                     // this value is obtained by calibrating the scale with known weights; see the README for details
    load_cellX.tare();                                // reset the scale to 0 for scale 1
    Serial.println("After setting up the scale:");
  
    Serial.print("read: \t\t");
    Serial.println(load_cellX.read());                // print a raw reading from the ADC for scale 1
  
    Serial.print("read average: \t\t");
    Serial.println(load_cellX.read_average(20));      // print the average of 20 readings from the ADC for scale 1

    Serial.print("get value: \t\t");
    Serial.println(load_cellX.get_value(5));          // print the average of 5 readings from the ADC minus the tare weight, set with tare() for scale 1
  
    Serial.print("get units: \t\t");
    Serial.println(load_cellX.get_units(5), 1);       // print the average of 5 readings from the ADC minus tare weight, divided by scale parameter wit set_scale
    Serial.println("Readings:");                     //Serial monitor readings
}

//read inputs from load cell and control LEDs accordinly 
void read_send(HX711 load_cellX){
    load_cellX.set_scale(CALIBRATION_FACTOR);         //Adjust to this calibration factor for scale 1
    Serial.print("sensor readings:\t");
    Serial.print(load_cellX.get_units(), 1);  
    Serial.print("      ");
    Serial.print("\t| average:\t");
    Serial.println(load_cellX.get_units(10), 1);
    Serial.println();
    Serial.println();
    
    int ledbrightness;   //Integer for the brightness of the LED lights    
    float forceC;
    float forceT;
      
    if (load_cellX.get_units() < NEGATIVE_FLOOR){     // testing if sensor 1 is in tension
      ledbrightness = ((map(load_cellX.get_units(), MIN_LB, 0, MAP_LOW, 255))*-1); //Convert the reading from the scale into a pwm output
      forceC = (((load_cellX.get_units() - MIN_LB)*(255-MAP_LOW))/((0-MIN_LB)+MAP_LOW));
      analogWrite(GREEN_LED, ledbrightness);
      analogWrite(RED_LED, 0);
      Serial.print("compression1");
      Serial.print("      ");
      Serial.print(forceC);
      Serial.print(" lbs");
      Serial.println(); 
    }else if (load_cellX.get_units() > POSITIVE_FLOOR){     //testing for compression in sensor 1
      ledbrightness = map(load_cellX.get_units(), 0, MAX_LB, MAP_LOW, 255);
      forceT = (((load_cellX.get_units() - 0)*(255-MAP_LOW))/((MAX_LB-0)+MAP_LOW));
      analogWrite(RED_LED, ledbrightness);
      analogWrite(GREEN_LED, 0);
      Serial.print("tension1");
      Serial.print("      ");
      Serial.print(forceT);
      Serial.print(" lbs");
      Serial.println(); 
    }else if (NEGATIVE_FLOOR <= load_cellX.get_units() <= POSITIVE_FLOOR){
      analogWrite(GREEN_LED, 0);
      analogWrite(RED_LED, 0);
      Serial.println("no load detected sensor 1");
      delay(DELAY);
    }
}
  
void set_calibration(HX711 lc){ //Refer to this link for the code: https://www.instructables.com/Arduino-Scale-With-5kg-Load-Cell-and-HX711-Amplifi/
   buttonState = digitalRead(buttonPin);
   
   if (buttonState == HIGH) {                   //Check if the pushbutton is pressed. If it is, the buttonState is HIGH (buttonState = 1)
      lc.set_scale(CALIBRATION_FACTOR);         //Adjust to this calibration factor for scale 1
      Serial.print("sensor readings:\t");
      Serial.print(lc.get_units(), 1);  
      Serial.print("      ");
      Serial.print("\t| average:\t");
      Serial.println(lc.get_units(10), 1);
      Serial.println();
      Serial.println();  
   }
}

void passiveDelay(int passiveDelayTime){
  if(millis() - lastUpdate >= passiveDelayTime){ //Check if timer is equal to or later than the collection time variable in config.h (in milliseconds)
    lastUpdate = millis(); //update old_time to current millis()
  }
}

void lcd(){
/* TODO:
 * Identify LCD pins & wiring
 * Setup LCD library
 * Setup LCD as an output jn the setup function
*/
}


/* LIBRARIES USED & TUTORIALS
 * 
 *  HX711: https://www.arduino.cc/reference/en/libraries/hx711-arduino-library/
 *  LOAD CELL AMPLIFIER HX711: https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all
 * 
*/
