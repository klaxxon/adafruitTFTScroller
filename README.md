# adafruitTFTScroller

[![Watch the video](https://github.com/klaxxon/adafruitTFTScroller/blob/master/scroller.png?raw=true)](https://www.youtube.com/watch?v=AX4G6JVqIOs&feature=youtu.be)

Sample of scrolling the HX8357 through hardware in portrait mode.  I wanted a way to dump Serial to this little screen, which required some sort of scrolling.  I could not find anything except the hardware manual for the chip to perform scrolling so I wrote this little class to implement a smooth scroll.  This class uses the AdaFruit HX8357 tft driver, but could probably be used with other drivers using similar hardware.<br/>
<br/>
You can get the board from here:<br/>
https://www.amazon.com/gp/product/B00TIYUWNY/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1<br/>
or AdaFruit directly at:<br/>
https://www.adafruit.com/?q=hxd8357d<br/>
<br/>
<br/>
<B>Class inherits from Print.</B><br/>
<b>Additional methods:</b><br/>
<code>  config(int rotation, int textsize);</code><br/>
    Calls the underlying TFT methods for rotation and text size.<br/>
<code>  setTextSize(int textsize);</code><br/>
    Sets text size. Can be used between calls to change text size between output calls.<br/>
<code>  setLinePadSize(int y);</code><br/>
    Sets number of pixels between each line of text. Defaults to two.<br/>
<br/>
<br/>
<b>Limitations:</b><br/>
No word wrap.  Currently truncates anything greater than max chars per line (320 / 8 * textsize).
