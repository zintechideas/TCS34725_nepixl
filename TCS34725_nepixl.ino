#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Adafruit_NeoPixel.h>
 #define LEDpin     7
#define NUMPIXELS  8  
 Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDpin, NEO_GRB + NEO_KHZ800);




#define commonAnode true


byte gammatable[256];


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
  pixels.begin();

 
  if (tcs.begin()) {
    
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); 
  }


  
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;

    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;
    }
    
  }
}


void loop() {
  float red, green, blue;
  
  tcs.setInterrupt(false);  // turn on LED

  delay(60);  // takes 50ms to read

  tcs.getRGB(&red, &green, &blue);
  
  tcs.setInterrupt(true);  // turn off LED

  Serial.print("R:\t"); Serial.print(int(red)); 
  Serial.print("\tG:\t"); Serial.print(int(green)); 
  Serial.print("\tB:\t"); Serial.print(int(blue));
 
  
 

  Serial.print("\n");



  for(int i=0;i<NUMPIXELS;i++){
    
  pixels.setPixelColor(i, pixels.Color((int)red,(int)green,(int)blue)); 
  pixels.show(); 
  delay(50); 
}

}
