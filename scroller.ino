/***************************************************
  This is our library for the Adafruit HX8357D Breakout
  ----> http://www.adafruit.com/products/2050

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"
#include "AdaScroller.h"

// These are 'flexible' lines that can be changed
#define TFT_CS 5
#define TFT_DC 21
#define TFT_RST -1 // RST can be set to -1 if you tie it to Arduino's reset
#define MISO 19

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, 23, 18, -1, MISO);

// SoftSPI - note that on some processors this might be *faster* than hardware SPI!
//Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, MOSI, SCK, TFT_RST, MISO);





Log2TFT logit(&tft);
// Redefine serial to display
#define Serial logit


void setup() {
  Serial.begin(115200);  // Does nothing with define above
  logit.config(0, 2);  // Portait mode, double text size
  logit.setTextColor(HX8357_WHITE);
  //tft.begin();
  Serial.println("HX8357D Test!"); 


  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(HX8357_RDPOWMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDCOLMOD);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDDIM);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDDSDR);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 
  
  Serial.println(F("Benchmark                Time (microseconds)"));

  Serial.println(F("Done!"));
}


// Simple byte to RGB short
unsigned short doCol(unsigned short in) {
  unsigned short col = 0;
  in &= 0xff;
  if (in <= 85) {
    col = (255-(3*in))&0xf8;
    col <<= 8;
    col |= ((in*3)&0xfc)<<3;
    return col;
  }
  if (in <= 170) {
    in -= 85;
    col = (255-(3*in))&0xfc;
    col <<= 3;
    col |= ((in*3)&0xf8)>>3;
    return col;
  }
  in -= 170;
  col = (in*3)&0xf8;
  col <<= 8;
  col |= ((255-(3*in))&0xf8)>>3;
  return col;
}



void loop(void) {
  static unsigned long cnt = 0;
  logit.setBackgroundColor(doCol(cnt*8));
  logit.setTextSize(1+(cnt%3));
  logit.print("0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF\n");
}


