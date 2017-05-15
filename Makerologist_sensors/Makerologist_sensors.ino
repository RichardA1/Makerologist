#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include <Adafruit_NeoPixel.h>

// Basic pin reading and pullup test for the MCP23017 I/O expander
// public domain!

// Connect pin #12 of the expander to Analog 5 (i2c clock)
// Connect pin #13 of the expander to Analog 4 (i2c data)
// Connect pins #15, 16 and 17 of the expander to ground (address selection)
// Connect pin #9 of the expander to 5V (power)
// Connect pin #10 of the expander to ground (common ground)
// Connect pin #18 through a ~10kohm resistor to 5V (reset pin, active low)

// Input #0 is on pin 21 so connect a button or switch from there to ground

Adafruit_MCP23017 mcp;
#define PIN 7
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

int Tottal = 0;

void setup() {  
  Serial.begin(9600);
  
  mcp.begin();      // use default address 0
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    mcp.pinMode(i, INPUT);
    mcp.pullUp(i, HIGH);  // turn on a 100K pullup internally
  }

  pinMode(13, OUTPUT);  // use the p13 LED as debugging
}

void loop() {
  // The LED will 'echo' the button
  Tottal = 0;
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    int reading = mcp.digitalRead(i);
    Serial.print(reading);
    Tottal = Tottal + reading;
  }
  
  Serial.print(" = ");
  Serial.println(Tottal);
  
 if(Tottal){
    digitalWrite(13, LOW);
  }else{
    digitalWrite(13, HIGH);
  }
  colorWipe(strip.Color(0, 255, 0)); // Green
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    if(!mcp.digitalRead(i)){
      strip.setPixelColor(i, c);
    }else{
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
  }
}
