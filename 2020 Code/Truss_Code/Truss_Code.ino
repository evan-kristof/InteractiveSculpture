/**

   HX711 library for Arduino - example file
   https://github.com/bogde /HX711

   MIT License
   (c) 2018 Bogdan Necula

**/

// Mashed together by Chris Larson


#include "HX711.h"
int maplow = 150;     //the lowest the map function will go (may help with delays)
int minlb = -150; //largest tension load expected on a sensor
int maxlb = 100; //largest compressive load expected on sensor
float negfloor = -5;   //minimum amount of force before led will activate for tension
float pfloor = 5 ;     //minimum amount of force before led will activate for compression
int del = 30;            //delays in if statments in loop.



// HX711 circuit wiring
const int LOADCELL_SCK_PIN1 = 2;
//const int LOADCELL_SCK_PIN2 = 22;
//const int LOADCELL_SCK_PIN3 = 24;
const int LOADCELL_DOUT_PIN1 = 3;
//const int LOADCELL_DOUT_PIN2 = 23;2
//const int LOADCELL_DOUT_PIN3 = 25;

// HX711 loadcell wiring
HX711 scale1 (LOADCELL_DOUT_PIN1, LOADCELL_SCK_PIN1);
//HX711 scale2 (LOADCELL_DOUT_PIN2, LOADCELL_SCK_PIN2);
//HX711 scale3 (LOADCELL_DOUT_PIN3, LOADCELL_SCK_PIN3);
float calibration_factor = -7050; //-7050 worked for my 440lb max scale setup //we used -3050 prev, i just changed it

void setup() {
  Serial.begin(9600);// Serial monitor reading
  delay(50);// a delay of 50 milliseconds
  pinMode(6, OUTPUT);//Output for the LED lights
  pinMode(7, OUTPUT);//Output for the LED lights
  //pinMode(8, OUTPUT);//Output for the LED lights
  //pinMode(9, OUTPUT);//Output for the LED lights
  //pinMode(10, OUTPUT);//Output for the LED lights
  //pinMode(11, OUTPUT);//Output for the LED lights



  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale1.read());     // print a raw reading from the ADC for scale 1
  //Serial.println(scale2.read());     // print a raw reading from the ADC for scale 2
  //Serial.println(scale3.read());     // print a raw reading from the ADC for scale 3
  Serial.print("read average: \t\t");
  Serial.println(scale1.read_average(20));   // print the average of 20 readings from the ADC for scale 1
  //Serial.println(scale2.read_average(20));   // print the average of 20 readings from the ADC for scale 2
  //Serial.println(scale3.read_average(20));   // print the average of 20 readings from the ADC for scale 3
  Serial.println("test");
  Serial.print("get value: \t\t");
  Serial.println(scale1.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet) for scale 1
  //Serial.println(scale2.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet) for scale 2
  //nSerial.println(scale3.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet) for scale 3

  Serial.print("get units: \t\t");
  Serial.println(scale1.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight for scale 1
//  Serial.println(scale2.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight for scale 2
 //Serial.println(scale3.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight for scale 3
 


  scale1.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale1.tare();               // reset the scale to 0 for scale 1
  //scale2.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  //scale2.tare();               // reset the scale to 0 for scale 2
  //scale3.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  //scale3.tare();               // reset the scale to 0 for scale 3

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale1.read());// print a raw reading from the ADC for scale 1
  //Serial.println(scale2.read());// print a raw reading from the ADC for scale 2
  //Serial.println(scale3.read());//print a raw reading from the ADC for scale 3

  Serial.print("read average: \t\t");
  Serial.println(scale1.read_average(20));// print the average of 20 readings from the ADC for scale 1
  delay(1000);
  //Serial.println(scale2.read_average(20));// print the average of 20 readings from the ADC for scale 2
  //Serial.println(scale3.read_average(20));// print the average of 20 readings from the ADC for scale 3

  Serial.print("get value: \t\t");
  Serial.println(scale1.get_value(5));// print the average of 5 readings from the ADC minus the tare weight, set with tare() for scale 1
  //Serial.println(scale2.get_value(5));// print the average of 5 readings from the ADC minus the tare weight, set with tare() for scale 2
  //Serial.println(scale3.get_value(5));// print the average of 5 readings from the ADC minus the tare weight, set with tare() for scale 3

  Serial.print("get units: \t\t");
  Serial.println(scale1.get_units(5), 1);// print the average of 5 readings from the ADC minus tare weight, divided by scale parameter wit set_scale
  //Serial.println(scale2.get_units(5), 1);// print the average of 5 readings from the ADC minus tare weight, divided by scale parameter wit set_scale
  //Serial.println(scale3.get_units(5), 1);// print the average of 5 readings from the ADC minus tare weight, divided by scale parameter wit set_scale

  Serial.println("Readings:");//Serial monitor readings


  delay(1000);//Delay in serialprint reading of 500 milliseconds
}

void loop() {
  scale1.set_scale(calibration_factor);//Adjust to this calibration factor for scale 1
  //scale2.set_scale(calibration_factor);//Adjust to this calibration factor for scale 2
  //scale3.set_scale(calibration_factor);//Adjust to this calibration factor for scale 3

  Serial.print("sensor readings:\t");
  Serial.print(scale1.get_units(), 1);  
  Serial.print("      ");
  //Serial.print(scale2.get_units(), 1);
  //Serial.print ("     ");
  //Serial.prin  t(scale3.get_units(), 1);
   Serial.print("\t| average:\t");
  Serial.println(scale1.get_units(10), 1);
  //Serial.println(scale2.get_units(10), 1);
  //Serial.println(scale3.get_units(10), 1);
  Serial.println();
  Serial.println();
  delay(1000);

  int ledbrightness;       //Interger for the brightness of the LED lights

  if (scale1.get_units() < negfloor) // testing if sensor 1 is in tension
  {
    ledbrightness  = ((map(scale1.get_units(), minlb, 0, maplow, 255))*-1); //Convert the reading from the scale into a pwm output

    analogWrite(6, ledbrightness);
    analogWrite(7, 0);
    Serial.print("compression1");
    Serial.print("      ");
    Serial.print(ledbrightness);
    Serial.println();
    delay(del);
  }
  else if (scale1.get_units() > pfloor)     //testing for compression in sensor 1
  {
    analogWrite(6, 0);
    ledbrightness  = map(scale1.get_units(), 0, maxlb, maplow, 255);
    analogWrite(7, ledbrightness);
    Serial.print("tension1");
    Serial.print("      ");
    Serial.print(ledbrightness);
    Serial.println(); 
    delay(del);
  }
  else if   (negfloor <=  scale1.get_units() <= pfloor) {
    analogWrite(6, 0);
    analogWrite(7, 0);
    Serial.println("no load detected sensor 1");
    delay(del);
  }}

  /*if (scale2.get_units() < negfloor)  //testing for tension in sensor 2
  {
    analogWrite(9, 0);
    ledbrightness  = ((map(scale2.get_units(), minlb, 0, maplow, 255))*-1);
    analogWrite(8, ledbrightness);
    Serial.print("compression2");
    Serial.print("      ");
    Serial.print(ledbrightness);
    Serial.println();
    delay(del);
  }
 // else if (scale2.get_units() > pfloor)     //testing for compression sensor 2
  {
    ledbrightness  = map(scale2.get_units(), 0, maxlb, maplow, 255);
    analogWrite(8, ledbrightness);
    Serial.print("tension2");
    Serial.print("      ");
    Serial.print(ledbrightness);
    Serial.println();
    analogWrite(9, 0); //TENSION
    delay(del);
  }
 /* else if (negfloor <=  scale2.get_units() <= pfloor) {
    analogWrite(8, 0);
    analogWrite(9, 0);
    Serial.println("no load detected sensor 2");
    delay(del);
  }

  if (scale3.get_units() < negfloor)   //testing tension sensor 3
  {
    analogWrite(10, 0);
    ledbrightness  = (((map(scale3.get_units(), minlb, 0, maplow, 255))*-1));
   
    analogWrite(11, ledbrightness);
    Serial.print("compression3");
    Serial.print("      ");
    Serial.print(ledbrightness);
    Serial.println();
    delay(del);
  }
  else if (scale3.get_units() > pfloor)   //testing compression sensor 3
  {

    analogWrite(11, 0);
    ledbrightness  = map(scale3.get_units(), 0, maxlb, maplow, 255);
    analogWrite(10, ledbrightness);
    Serial.print("tension3");
    Serial.print("      ");
    Serial.print(ledbrightness);
    Serial.println();
    delay(del);

  }
  else if (negfloor <=  scale3.get_units() <= pfloor) {
    analogWrite(11, 0);
    analogWrite(10, 0);
    Serial.println("no load detected sensor 3");
    delay(del);
  }
}

/* else {                 //clears all leds, if no load is detected.
   analogWrite(6, 0);
   analogWrite(7, 0);
   analogWrite(8, 0);
  analogWrite(9, 0);
  analogWrite(10, 0);
  analogWrite(11, 0);
  Serial.println("no load detected");
  delay(del); */


/*
  scale1.power_down();       //i commented this out in case it was the reason for the delay.
  scale2.power_down();
  scale3.power_down();
  delay(5);
  scale1.power_up();
  scale2.power_up();
   scale3.power_up();
*/
