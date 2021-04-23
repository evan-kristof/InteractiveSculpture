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
#define LOADCELLa_SCK_PIN 2
#define LOADCELLa_DT_PIN 3
#define LOADCELLb_SCK_PIN 4
#define LOADCELLb_DT_PIN 5
#define LOADCELLc_SCK_PIN 6
#define LOADCELLc_DT_PIN 6

//HX711 LOAD CELL CALIBRATION FACTOR (Note: -7050 worked for 440lb max scale setup. Used -3050 previously)
#define CALIBRATION_FACTOR -7050

//BUTTON FUNCTIONALITY
#define buttonPin 2           // the number of the pushbutton pin
#define buttonState 0         // variable for reading the pushbutton status

//DELAY CODE (IN MILLISECONDS)
#define DELAY 0 

//PASSIVE DELAY TIME (MILLISECONDS)
#define COLLECT_TIME 6000

//ESTIMATED MAX & MIN LOADINGS ON LOAD CELL IN LBS
#define MIN_LB -50         //largest tension load expected on a sensor
#define MAX_LB 50          //largest compressive load expected on sensor

//MINIMUM AMOUNT OF LBS TO ACTIVATE LEDS
#define MAP_LOW 30           //the lowest the map function will go (may help with delays)
#define NEGATIVE_FLOOR -1    //minimum amount of force before led will activate for tension
#define POSITIVE_FLOOR 1     //minimum amount of force before led will activate for compression

//DEFINE PINS FOR LED
#define RED_LED 6           //TENSION
#define GREEN_LED 7         //COMPRESSION
#define BLUE_LED 8


#endif
