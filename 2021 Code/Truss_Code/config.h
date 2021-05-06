/* Interactive Sculpture Truss Code
 * This file contains pin values. If you wish to modify the pins/circuitry, ensure you updae the values in the config.h file for the code to work properly
 * 
 * config.h
 * 
 * DATE CREAED: 1/29/21 BY OMAR WAKED
 * DATE MODIFIED: 1/29/21 BY OMAR WAKED
 * IMPORTANT: UPDATE THE MODIFIED DATE AND NAME ABOVE 
 * LINK TO CODE ON GITHUB: https://github.com/OmarWaked/InteractiveSculpture.git
*/

#ifndef CONFIG_H
#define CONFIG_H

//DEFINE HX711 LOAD CELL PINS
//load cell 1
#define LOADCELL_SCK_PIN1 2
#define LOADCELL_DT_PIN1 3
//load cell 2
#define LOADCELL_SCK_PIN2 4
#define LOADCELL_DT_PIN2 5
//Load cell 3
#define LOADCELL_SCK_PIN3 6
#define LOADCELL_DT_PIN3 7

//HX711 LOAD CELL CALIBRATION FACTOR (Note: -7050 worked for 440lb max scale setup. Used -3050 previously)
const float SCALE = 27470;

//CALIBRATION BUTTON
#define buttonPin 8           // the pin of the pushbutton
#define KNOWN_WEIGHT 15       // lbs

//ESTIMATED MAX & MIN LOADINGS ON LOAD CELL IN LBS
const float MIN_LB = -5.0;         //largest COMPRESSION load expected on a sensor
const float MAX_LB = 5.0;          //largest TENSION load expected on sensor

//MINIMUM AMOUNT OF LBS TO ACTIVATE LEDS
const float MAP_LOW = 0.0;           //the lowest the map function will go (may help with delays)
#define NEGATIVE_FLOOR -0.1    //minimum amount of force before led will activate for tension
#define POSITIVE_FLOOR 0.1     //minimum amount of force before led will activate for compression

//DEFINE PINS FOR LED
#define RED_LED 6           //TENSION
#define GREEN_LED 7         //COMPRESSION
#define BLUE_LED 8


#endif
