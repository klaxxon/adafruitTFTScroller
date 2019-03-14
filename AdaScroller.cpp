#include "AdaScroller.h";
#include <SPI.h>
#include "Adafruit_GFX.h"


Log2TFT::Log2TFT(Adafruit_HX8357 *tft) {
  tft_ = tft;
}

void Log2TFT::begin(int){}

void Log2TFT::setTextSize(int x) {
  tft_->setTextSize(x);
  charsize_ = x * 8;
  bsize_ = 1+dwidth_/(x*6);
}

void Log2TFT::setLinePadSize(int x) {
  yspacing_ = x;
}

void Log2TFT::config(int rotation, int fontsize) {
  tft_->begin();
  tft_->setTextWrap(false); // Don't wrap text to next line
  tft_->setRotation(rotation);
  if (!rotation) {
    dwidth_ = 320;
    dheight_ = 480;
  }
  else {
    dwidth_ = 480;
    dheight_ = 320;
  }
  yspacing_ = 2;
  setTextSize(fontsize);
  blen_ = 0;
  scrollPos_ = 0;
  tft_->setTextColor(0xe79c);
}


void Log2TFT::scrollAddress(uint16_t VSP) {
  tft_->writeCommand(0x37); 
  tft_->SPI_WRITE16(VSP);
}

void Log2TFT::setupScrollArea(uint16_t TFA, uint16_t BFA) {
  tft_->writeCommand(0x33); 
  tft_->SPI_WRITE16(TFA);
  tft_->SPI_WRITE16(dheight_ - TFA - BFA);
  tft_->SPI_WRITE16(BFA);
}


void Log2TFT::scroll() {
  tft_->startWrite();
  setupScrollArea(0, 0);
  scrollAddress(scrollPos_);
  tft_->endWrite();
  if (!scrollPos_) scrollPos_ = dheight_;
  scrollPos_--;
  tft_->drawLine(0, dheight_-1-scrollPos_, dwidth_, dheight_-1-scrollPos_, bgroundColor_);
  return;
}

size_t Log2TFT::write(uint8_t x) {
  if (x == 10) {
    for(int a=0;a<charsize_+yspacing_;a++) scroll();
    buf_[blen_] = 0;
    int y = dheight_-charsize_-scrollPos_;
    if (y < 0) {  // In case we are on a non-8 divisible boundary
      tft_->setCursor(0, y);
      tft_->setTextColor(textColor_);
      tft_->print(buf_);
      y += dheight_;
    }
    tft_->setCursor(0, y);
    tft_->print(buf_);
    blen_ = 0;
  }
  else {
    if (blen_ < bsize_-1) {
      buf_[blen_++] = x;
    }
  }
}

Log2TFT::RECT Log2TFT::getCurrentLineBounds() {
  RECT b = {0, dheight_-charsize_-scrollPos_, dwidth_, charsize_};
  return b;
}
