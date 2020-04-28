#include "Arduino.h"
#include "buttonTrigger.h"
#include "buttonClass.h"

#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

long timer = 0;         // use this to store times for timers

// digital pins 
#define LED_PIN1    5
#define LED_PIN2     6
#define LED_PIN3   7
#define LED_PIN4    8
#define LED_PIN5   9
#define LED_PIN6   10
#define LED_PIN7   11
#define LED_PIN8   12

//change colour of the lights here:
int r = 255;
int g = 77;
int b = 0;
int w = 32;

// after n amount of time the lights go off
int timeoff = 30;

#define LED_COUNT     15
bool buttonPushed = false;
Adafruit_NeoPixel strip1(LED_COUNT, LED_PIN1, NEO_GRBW + NEO_KHZ800); // ground and basement
Adafruit_NeoPixel strip2(LED_COUNT, LED_PIN2, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel strip3(LED_COUNT, LED_PIN3, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel strip4(LED_COUNT, LED_PIN4, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel strip5(LED_COUNT, LED_PIN5, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel strip6(LED_COUNT, LED_PIN6, NEO_GRBW + NEO_KHZ800);

Adafruit_NeoPixel strip7(LED_COUNT, LED_PIN7, NEO_GRBW + NEO_KHZ800); // gate house
Adafruit_NeoPixel strip8(LED_COUNT, LED_PIN8, NEO_GRBW + NEO_KHZ800); // gate house

int buttonRelease = false;
int state = 0;

Button myButton(4);

int buttonPressCounter = 0;

void setup() 
{
  // put your setup code here, to run once:
  myButton.begin();

  Serial.begin(19200);
  strip1.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip1.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  strip2.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip2.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  strip3.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip3.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  strip4.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip4.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  strip5.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip5.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  strip6.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip6.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  strip7.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip7.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  strip8.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip8.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  for (int j = 0; j < LED_COUNT; j++)
  {
    strip1.setPixelColor(j, 0, 0, 0, 0);
    strip2.setPixelColor(j, 0, 0, 0, 0);
    strip3.setPixelColor(j, 0, 0, 0, 0);
    strip4.setPixelColor(j, 0, 0, 0, 0);
    strip5.setPixelColor(j, 0, 0, 0, 0);
    strip6.setPixelColor(j, 0, 0, 0, 0);
    strip7.setPixelColor(j, 0, 0, 0, 0);
    strip8.setPixelColor(j, 0, 0, 0, 0);
  }

  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
  strip7.show();
  strip8.show();
}

void loop()
{
  if (state == 0)
  {
    if (myButton.isPushed() && buttonRelease == false )
    {
      buttonPressCounter += 1; // button counter = 1
      buttonRelease = true; 
      
      Serial.println("pushed");
      for (int j = 0; j < LED_COUNT; j++)
      {
        strip1.setPixelColor(j, r, g, b, w);
        strip2.setPixelColor(j, r, g, b, w);
        strip3.setPixelColor(j, r, g, b, w);
        strip4.setPixelColor(j, r, g, b, w);
        strip5.setPixelColor(j, r, g, b, w);
        strip6.setPixelColor(j, r, g, b, w);
        strip7.setPixelColor(j, r, g, b, w);
        strip8.setPixelColor(j, r, g, b, w);
      }

      strip1.show();
      strip2.show();
      strip3.show();
      strip4.show();
      strip5.show();
      strip6.show();
      strip7.show();
      strip8.show();
      Serial.println("lights on");
      state = 1;
      timer = millis();
    }
  }
  else if (state == 1)
  {

    //turn off lights if button pushed again 
    if(myButton.isPushed() && buttonRelease == true) 
    {
        buttonPressCounter += 1; // count is 2 
        Serial.println("button pushed");
        buttonRelease = false; 
        
        for (int j = 0; j < LED_COUNT; j++)
        {
          strip1.setPixelColor(j, 0, 0, 0, 0);
          strip2.setPixelColor(j, 0, 0, 0, 0);
          strip3.setPixelColor(j, 0, 0, 0, 0);
          strip4.setPixelColor(j, 0, 0, 0, 0);
          strip5.setPixelColor(j, 0, 0, 0, 0);
          strip6.setPixelColor(j, 0, 0, 0, 0);
          strip7.setPixelColor(j, 0, 0, 0, 0);
          strip8.setPixelColor(j, 0, 0, 0, 0);
        }
        strip1.show();
        strip2.show();
        strip3.show();
        strip4.show();
        strip5.show();
        strip6.show();
        strip7.show();
        strip8.show();

        Serial.println("lights off");
        timer = millis();
        state = 0;
    }

   //if the lights have been on for longer than 30 secs or 30 then turn light off
    
    if(millis() >= timer + timeoff * 1000)
    {
      for (int j = 0; j < LED_COUNT; j++)
        {
          strip1.setPixelColor(j, 0, 0, 0, 0);
          strip2.setPixelColor(j, 0, 0, 0, 0);
          strip3.setPixelColor(j, 0, 0, 0, 0);
          strip4.setPixelColor(j, 0, 0, 0, 0);
          strip5.setPixelColor(j, 0, 0, 0, 0);
          strip6.setPixelColor(j, 0, 0, 0, 0);
          strip7.setPixelColor(j, 0, 0, 0, 0);
          strip8.setPixelColor(j, 0, 0, 0, 0);
        }
        strip1.show();
        strip2.show();
        strip3.show();
        strip4.show();
        strip5.show();
        strip6.show();
        strip7.show();
        strip8.show();  
        Serial.println("timer is greater than 30 turn off lights");
        Serial.println("lights off");
        buttonRelease = false; 
        state = 0;
    }
   // if the button is pushed more than twice keep it on 
  if(buttonPressCounter >= 2 && millis() >= timer + 5 *1000) 
    {
      buttonRelease = true;
      
      for (int j = 0; j < LED_COUNT; j++)
      {
        strip1.setPixelColor(j, r, g, b, w);
        strip2.setPixelColor(j, r, g, b, w);
        strip3.setPixelColor(j, r, g, b, w);
        strip4.setPixelColor(j, r, g, b, w);
        strip5.setPixelColor(j, r, g, b, w);
        strip6.setPixelColor(j, r, g, b, w);
        strip7.setPixelColor(j, r, g, b, w);
        strip8.setPixelColor(j, r, g, b, w);
      }

      strip1.show();
      strip2.show();
      strip3.show();
      strip4.show();
      strip5.show();
      strip6.show();
      strip7.show();
      strip8.show();
      
      Serial.println("lights on button pushed more than twice cannot repush wait 3 seconds");
      timer = millis();
      state = 2;
    }
  }
    // keep the lights on for 5 seconds and then allow the button to be pushed again 
   if(state == 2)
    
    {
      Serial.println("reset button off");
      buttonRelease = false;
      buttonPressCounter = 0;
      state = 0;
    }
 
}
