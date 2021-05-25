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
#define LOADCELL_SCK_PIN1 9
#define LOADCELL_DT_PIN1 8
//load cell 2
//#define LOADCELL_SCK_PIN2 4
//#define LOADCELL_DT_PIN2 5
//Load cell 3
//#define LOADCELL_SCK_PIN3 6
//#define LOADCELL_DT_PIN3 7

//HX711 LOAD CELL CALIBRATION FACTOR (Note: -7050 worked for 440lb max scale setup. Used -3050 previously)
//const float SCALE = 19470;

// passive delay for LCD screen
const long passiveDelayTime = 2000;

//CALIBRATION BUTTON
#define buttonPin 52           // the pin of the pushbutton
const float KNOWN_WEIGHT = 15.0;       // lbs
const float CONFIG_FACTOR = 1.00; // 60-60-60 triangle: CONFIG_FACTOR = 1.73, 45-45-90 triangle: CONFIG_FACTOR = ..., 30-60-90 triangle: CONFIG_FACTOR = ....

//ESTIMATED MAX & MIN LOADINGS ON LOAD CELL IN LBS
const float MIN_LB = -30.0;         //largest COMPRESSION load expected on a sensor
const float MAX_LB = 30.0;          //largest TENSION load expected on sensor

//MINIMUM AMOUNT OF LBS TO ACTIVATE LEDS
const float MAP_LOW = 0.0;           //the lowest the map function will go (may help with delays)
float NEGATIVE_FLOOR = -0.10;    //minimum amount of force before led will activate for tension
float POSITIVE_FLOOR = 0.10;     //minimum amount of force before led will activate for compression

//DEFINE PINS FOR LED
#define RED_LED 10           //TENSION
#define GREEN_LED 11         //COMPRESSION
#define BLUE_LED 12


#endif
