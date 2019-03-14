#ifndef __ADASCROLLER_H__
#define __ADASCROLLER_H__
#include "Adafruit_HX8357.h"

class Log2TFT : public Print {
  public:
  typedef struct RECT {
    unsigned short x, y, w, h;
  } RECT;
  
  Log2TFT(Adafruit_HX8357 *tft);
  void begin(int);
  void setTextSize(int x);
  void setLinePadSize(int x);
  void config(int rotation, int fontsize);
  void setTextColor(unsigned short col) {textColor_ = col; }
  void setBackgroundColor(unsigned short col) {bgroundColor_ = col; }
  size_t write(uint8_t x);
  RECT getCurrentLineBounds();

  private:
    void scrollAddress(uint16_t VSP);
    void setupScrollArea(uint16_t TFA, uint16_t BFA);
    void scroll();

    Adafruit_HX8357 *tft_;
    char buf_[64];
    unsigned char bsize_;
    unsigned char blen_;
    unsigned short scrollPos_;
    unsigned char charsize_;
    unsigned short dwidth_, dheight_;
    unsigned char yspacing_;
    unsigned short textColor_;
    unsigned short bgroundColor_;
};

#endif
