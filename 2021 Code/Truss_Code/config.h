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

//HX711 LOAD CELL PINS DECLARATION
#define LOADCELL_SCK_PIN 2
#define LOADCELL_DT_PIN 3

//HX711 LOAD CELL CALIBRATION FACTOR (Note: -7050 worked for 440lb max scale setup. Used -3050 previously)
#define CALIBRATION_FACTOR -7050

//DELAY CODE (IN MILLISECONDS)
#define DELAY 30 

//ESTIMATED MAX & MIN LOADINGS ON LOAD CELL IN LBS
#define MIN_LB  -150  //largest tension load expected on a sensor
#define MAX_LB 150    //largest compressive load expected on sensor

#endif
