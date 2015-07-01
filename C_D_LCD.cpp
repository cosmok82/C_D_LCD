/*
* The MIT License (MIT)
* 
* Copyright (c) 2015, all text above must be included in any redistribution.
* 
* Written by Cosimo Orlando (http://www.creativityslashdesign.tk)
* 
* This is a library for the S6D02A1/ST7735 display, model TFTM1802SPI,
* 1.8" TFT Breakout with w/SD card.
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include "C_D_LCD.h"


/* This function transmits a command to the LCD driver */
void C_D_LCD::LCDCommand(uint8_t datacmd)
{
	RS_Write(LOW);
	SPI.write(datacmd);
}
/*******************************************************/

/* This function transmits a data to the LCD driver */
void C_D_LCD::LCDData(uint8_t datadt)
{
	RS_Write(HIGH);
	SPI.write(datadt);
}
/*******************************************************/

void C_D_LCD::ResetDispaly(void)
{
	RST_Write(HIGH);
	delay(10);
	RST_Write(LOW);
	delay(10);
	RST_Write(HIGH);
	delay(10);
}
/*******************************************************/

void C_D_LCD::initSPIM(void)
{
	TFT_RS_init();
	TFT_RST_init();
	SPI.begin();
	SPI.setHwCs(1);
	SPI.setFrequency(40000000);
	SPI.setDataMode(SPI_MODE0);
	SPI.setBitOrder(MSBFIRST);
	delay(100);
};
/*******************************************************/

void C_D_LCD::initDISPLAY(void)
{
    x_start   = y_start = 0u;                       /* May be overridden in begin function. */
	rotation  = 0u;
	textsize  = 1u;
	wrap      = true;
	textcolor = textbgcolor = WHITE;
	
    initSPIM();
	ResetDispaly();
	
    LCDCommand(0xF0);
    LCDData(0x5A); LCDData(0x5A);                   /* Excommand2. */
	
    LCDCommand(0xFC);
    LCDData(0x5A); LCDData(0x5A);                   /* Excommand3. */
	
    LCDCommand(0x26);
    LCDData(0x01);                                  /* Gamma set. */
	
    LCDCommand(0xFA);
    LCDData(0x02); LCDData(0x1F); LCDData(0x00);
    LCDData(0x10); LCDData(0x22); LCDData(0x30);
    LCDData(0x38); LCDData(0x3A); LCDData(0x3A);
    LCDData(0x3A); LCDData(0x3A); LCDData(0x3A);
    LCDData(0x3D); LCDData(0x02); LCDData(0x01);	/* Positive gamma control. */
	
    LCDCommand(0xFB);
    LCDData(0x21); LCDData(0x00); LCDData(0x02);
    LCDData(0x04); LCDData(0x07); LCDData(0x0A);
    LCDData(0x0B); LCDData(0x0C); LCDData(0x0C);
    LCDData(0x16); LCDData(0x1E); LCDData(0x30);
    LCDData(0x3F); LCDData(0x01); LCDData(0x02);	/* Negative gamma control. */
	
    /*********** power setting sequence **********/
    
    LCDCommand(0xFD);
    LCDData(0x00); LCDData(0x00); LCDData(0x00);
    LCDData(0x17); LCDData(0x10); LCDData(0x00);
    LCDData(0x01); LCDData(0x01); LCDData(0x00);
    LCDData(0x1F); LCDData(0x1F);                   /* Analog parameter control. */
	
    LCDCommand(0xF4);
    LCDData(0x00); LCDData(0x00); LCDData(0x00);
    LCDData(0x00); LCDData(0x00); LCDData(0x3F);
    LCDData(0x3F); LCDData(0x07); LCDData(0x00);
    LCDData(0x3C); LCDData(0x36); LCDData(0x00);
    LCDData(0x3C); LCDData(0x36); LCDData(0x00);	/* Power control. */
	
    LCDCommand(0xF5);
    LCDData(0x00); LCDData(0x70); LCDData(0x66);
    LCDData(0x00); LCDData(0x00); LCDData(0x00);
    LCDData(0x00); LCDData(0x00); LCDData(0x00);
    LCDData(0x00); LCDData(0x6D); LCDData(0x66);
    LCDData(0x06);                                  /* VCOM control. */
	
    LCDCommand(0xF6);
    LCDData(0x02); LCDData(0x00); LCDData(0x3F);
    LCDData(0x00); LCDData(0x00); LCDData(0x00);
    LCDData(0x02); LCDData(0x00); LCDData(0x06);
    LCDData(0x01); LCDData(0x00);                   /* Source control. */
	
    /*********** initializing sequence ***********/
    
    LCDCommand(0xF2);
    LCDData(0x00); LCDData(0x01); /*04*/ LCDData(0x03);
    LCDData(0x08); LCDData(0x08); LCDData(0x04);
    LCDData(0x00); LCDData(0x00); LCDData(0x00);
    LCDData(0x00); LCDData(0x00); LCDData(0x01);
    LCDData(0x00); LCDData(0x00); LCDData(0x04);
    LCDData(0x08); LCDData(0x08);                   /* Display control. */
	
    LCDCommand(0xF8);
    LCDData(0x11);                                  /* Gate control. */
	
    LCDCommand(0xF7);
    LCDData(0xC8); LCDData(0x20); LCDData(0x00);
    LCDData(0x00);	                                /* Interface control. */
    
    LCDCommand(0xF3);
    LCDData(0x00);
    LCDData(0x00);	                                /* Power sequence control. */
	
    LCDCommand(SLEEPOUT);
    delay(50);                                      /* Wake. */
	
    LCDCommand(0xF3);
    LCDData(0x00); LCDData(0x01);
    delay(50);	                                	/* Power sequence control. */
	
    LCDCommand(0xF3);
    LCDData(0x00); LCDData(0x03);
    delay(50);	                                	/* Power sequence control. */
	
    LCDCommand(0xF3);
    LCDData(0x00); LCDData(0x07);
    delay(50);	                                	/* Power sequence control. */
	
    LCDCommand(0xF3);
    LCDData(0x00); LCDData(0x0F);
    delay(50);	                                	/* Power sequence control. */
	
    LCDCommand(0xF4);
    LCDData(0x00); LCDData(0x04); LCDData(0x00);
    LCDData(0x00); LCDData(0x00); LCDData(0x3F);
    LCDData(0x3F); LCDData(0x07); LCDData(0x00);
    LCDData(0x3C); LCDData(0x36); LCDData(0x00);
    LCDData(0x3C); LCDData(0x36); LCDData(0x00);
    delay(50);	                                	/* Power control. */
	
    LCDCommand(0xF3);
    LCDData(0x00); LCDData(0x1F);
    delay(50);	                                	/* Power sequence control. */
	
    LCDCommand(0xF3);
    LCDData(0x00); LCDData(0x7F);
    delay(50);	                                	/* Power sequence control. */
	
    LCDCommand(0xF3);
    LCDData(0x00); LCDData(0xFF);
    delay(50);	                                	/* Power sequence control. */
    
    LCDCommand(0xFD);
    LCDData(0x00); LCDData(0x00); LCDData(0x00);
    LCDData(0x17); LCDData(0x10); LCDData(0x00);
    LCDData(0x00); LCDData(0x01); LCDData(0x00);
    LCDData(0x16); LCDData(0x16);                   /* Analog parameter control. */

    LCDCommand(0xF4);
    LCDData(0x00); LCDData(0x09); LCDData(0x00);
    LCDData(0x00); LCDData(0x00); LCDData(0x3F);
    LCDData(0x3F); LCDData(0x07); LCDData(0x00);
    LCDData(0x3C); LCDData(0x36); LCDData(0x00);
    LCDData(0x3C); LCDData(0x36); LCDData(0x00);    /* Power control. */

    LCDCommand(MADCTL);                             /* Memory access data control. */
    LCDData(0x08);    
    LCDCommand(0x35);                               /* Tearing effect line on. */
    LCDData(NOP);
	LCDCommand(DISPON);                             /* Display on. */
    LCDCommand(RAMWR);                              /* Memory write. */
    
    _width  = WIDTH;
    _height = HEIGHT;
}
/*******************************************************/

void C_D_LCD::begin(void)
{
	initDISPLAY();
}
/*******************************************************/

void C_D_LCD::setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
  LCDCommand(CASET);      /* column addr set */
  LCDData(NOP);  
  LCDData(x0+x_start);    /* XSTART          */
  LCDData(NOP);
  LCDData(x1+x_start);    /* XEND            */
  LCDCommand(RASET);      /* row addr set    */
  LCDData(NOP);
  LCDData(y0+y_start);    /* YSTART          */
  LCDData(NOP);
  LCDData(y1+y_start);    /* YEND            */

  LCDCommand(RAMWR);      /* write to RAM    */
}
/*******************************************************/
void C_D_LCD::fillColor(uint32_t color)
{ 
  RS_Write(HIGH);
  SPI.write((uint8_t) color);
  SPI.write((uint8_t)(color >> 8));
  SPI.write((uint8_t)(color >> 16));
}
/*******************************************************/
void C_D_LCD::drawPixel(uint16_t x, uint16_t y, uint32_t color)
{
  if((x < 0) || (x >= _width) || (y < 0) || (y >= _height)) return;
 
  setAddrWindow(x,y,x+1,y+1);
  
  fillColor(color);
}
/*******************************************************/
void C_D_LCD::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color)
{
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  
  if (steep) { swap(x0, y0); swap(x1, y1); }

  if (x0 > x1) { swap(x0, x1); swap(y0, y1); }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1)
  {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0<=x1; x0++)
  {
    if (steep)
    {
      drawPixel(y0, x0, color);
    } else
    {
      drawPixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0)
    {
      y0 += ystep;
      err += dx;
    }
  }
}
/*******************************************************/
void C_D_LCD::setWidth(uint8_t d)
{
    if (d == NULL)
        _width = WIDTH;
    else
        _width = d;
}
/*******************************************************/
void C_D_LCD::setHeight(uint8_t d)
{
    if (d == NULL)
        _height = HEIGHT;
    else
        _height = d;
}
/*******************************************************/
uint8_t C_D_LCD::getWidth(void) const
{
    return _width;
}
/*******************************************************/
uint8_t C_D_LCD::getHeight(void) const
{
    return _height;
}
/*******************************************************/

/* some definition... */
#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04

/* Set Display rotation. */
void C_D_LCD::setRotation(uint8_t m)
{
  LCDCommand(MADCTL);
  rotation = m % 4; /* can't be higher than 3 */
  switch (rotation)
  { 
    case 0: 		/* portrait 0°            */
    LCDData(MADCTL_BGR);
    _width  = WIDTH;
    _height = HEIGHT;
    break;
    
    case 1: 		/* landscape 90°  		  */
    LCDData(MADCTL_MX | MADCTL_MV | MADCTL_BGR);
    _width  = HEIGHT;
    _height = WIDTH;
    break;
    
    case 2: 		/* portrait 180°		  */
    LCDData(MADCTL_MX | MADCTL_MY | MADCTL_BGR);
    _width  = WIDTH;
    _height = HEIGHT;
    break;
    
    case 3: 		/* landscape 270°		  */
    LCDData(MADCTL_MY | MADCTL_MV | MADCTL_BGR);
    _width  = HEIGHT;
    _height = WIDTH;
    break;
  }
}
/*******************************************************/
void C_D_LCD::drawFastVLine(int16_t x, int16_t y, int16_t h, uint32_t color)
{  
  /* Rudimentary clipping */
  if((x < 0) || (x >= _width) || (y < 0) || (y >= _height)) return;
  if((y+h-1) >= _height)  h = _height-y;
  
  setAddrWindow(x, y, x, y+h-1);

  while (h--) {
    fillColor(color);
  }
}
/*******************************************************/
void C_D_LCD::drawFastHLine(int16_t x, int16_t y, int16_t w, uint32_t color)
{
  /* Rudimentary clipping */
  if((x < 0) || (x >= _width) || (y < 0) || (y >= _height)) return;
  if((x+w-1) >= _width)  w = _width-x;
  setAddrWindow(x, y, x+w-1, y);

  while (w--) {
    fillColor(color);
  }
}
/*******************************************************/
void C_D_LCD::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color)
{
  drawFastHLine(x, y, w, color);
  drawFastHLine(x, y+h-1, w, color);
  drawFastVLine(x, y, h, color);
  drawFastVLine(x+w-1, y, h, color);
}
/*******************************************************/
void C_D_LCD::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color)
{
  uint16_t i;
  for (i = x; i < x+w; i++) {
    drawFastVLine(i, y, h, color);
  }
}
/*******************************************************/
void C_D_LCD::fillScreen(uint32_t color)
{
  fillRect(0, 0, _width, _height, color);
}
/*******************************************************/
void C_D_LCD::lcdTest(void)
{
  uint8_t i;
  for (i = 0; i < 100; i++) drawPixel(i, i, WHITE);
}
/*******************************************************/
void C_D_LCD::drawCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color)
{
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  /* center */
  drawPixel(x0    , y0 + r, color);
  drawPixel(x0    , y0 - r, color);
  drawPixel(x0 + r, y0    , color);
  drawPixel(x0 - r, y0    , color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
	
    drawPixel(x0 + x, y0 + y, color);
    drawPixel(x0 - x, y0 + y, color);
    drawPixel(x0 + x, y0 - y, color);
    drawPixel(x0 - x, y0 - y, color);
    drawPixel(x0 + y, y0 + x, color);
    drawPixel(x0 - y, y0 + x, color);
    drawPixel(x0 + y, y0 - x, color);
    drawPixel(x0 - y, y0 - x, color);
  }
}
/*******************************************************/
void C_D_LCD::drawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint32_t color)
{
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x4) {
      drawPixel(x0 + x, y0 + y, color);
      drawPixel(x0 + y, y0 + x, color);
    } 
    if (cornername & 0x2) {
      drawPixel(x0 + x, y0 - y, color);
      drawPixel(x0 + y, y0 - x, color);
    }
    if (cornername & 0x8) {
      drawPixel(x0 - y, y0 + x, color);
      drawPixel(x0 - x, y0 + y, color);
    }
    if (cornername & 0x1) {
      drawPixel(x0 - y, y0 - x, color);
      drawPixel(x0 - x, y0 - y, color);
    }
  }
}
/*******************************************************/

/* Used to do circles and roundrects. */
void C_D_LCD::fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint32_t color)
{
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x1) {
      drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
    }
    if (cornername & 0x2) {
      drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
    }
  }
}
/*******************************************************/
void C_D_LCD::fillCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color)
{
  drawFastVLine(x0, y0-r, 2*r+1, color);
  fillCircleHelper(x0, y0, r, 3, 0, color);
}
/*******************************************************/

/* Fill a rounded rectangle. */
void C_D_LCD::fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint32_t color)
{
  /* smarter version   */
  fillRect(x+r, y, w-2*r, h, color);

  /* draw four corners */
  fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
  fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}
/*******************************************************/
void C_D_LCD::drawChar(int16_t x, int16_t y, unsigned char c, uint32_t color, uint32_t bg, uint8_t size)
{
  if((x >= _width)            || /* Clip right  */
    ( y >= _height)           || /* Clip bottom */
    ((x + 6 * size - 1) < 0)  || /* Clip left   */
    ((y + 8 * size - 1) < 0))    /* Clip top    */
    return;

  int8 i;

  for (i = 0; i < 6; i++ ) {
    uint8_t line;
    if (i == 5) 
      line = 0x0;
    else 
      line = font[c*5+i];
    int8 j;
    for (j = 0; j < 8; j++) {
      if (line & 0x1) {
        if (size == 1)          /* default size */
          drawPixel(x+i, y+j, color);
        else {                  /* big size     */
          fillRect(x+(i*size), y+(j*size), size, size, color);
        } 
      } else if (bg != color) {
        if (size == 1)          /* default size */
          drawPixel(x+i, y+j, bg);
        else {                  /* big size     */
          fillRect(x+i*size, y+j*size, size, size, bg);
        }
      }
      line >>= 1;
    }
  }
}
/*******************************************************/
void C_D_LCD::setCursor(int8_t x, int8_t y) {
  cursor_x = x;
  cursor_y = y;
}
/*******************************************************/
void C_D_LCD::setTextSize(uint8_t s) {
  textsize = (s > 0) ? s : 1;
}
/*******************************************************/
void C_D_LCD::setTextColor(uint32_t c) {
  /*
   * For 'transparent' background, we'll set the bg 
   * to the same as fg instead of using a flag.
   */
  textcolor = textbgcolor = c;
}
/*******************************************************/
void C_D_LCD::setTextColor(uint32_t c, uint32_t b) {
  textcolor   = c;
  textbgcolor = b; 
}
/*******************************************************/
void C_D_LCD::setTextWrap(boolean w) {
  wrap = w;
}
/*******************************************************/
uint8_t C_D_LCD::getRotation(void) const {
  return rotation;
}
/*******************************************************/
size_t C_D_LCD::write(uint8_t c) {
  if (c == '\n') {
    cursor_y += textsize*8;
    cursor_x  = 0;
  } else if (c == '\r') {
    /* skip em */
  } else {
    drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
    cursor_x += textsize*6;
    if (wrap && (cursor_x > (_width - textsize*6))) {
      cursor_y += textsize*8;
      cursor_x = 0;
    }
	if (wrap && (cursor_y > (_height - textsize*6))) {
      cursor_y = 0;
      cursor_x = 0;
    }
  }
  
  return 1;
}