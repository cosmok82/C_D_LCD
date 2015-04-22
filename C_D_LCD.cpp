/**************************************************************************
This is a library for the S6D02A1/ST7735 display,
model TFTM1802SPI, 1.8" TFT Breakout with w/SD card.
----> http://www.creativityslashdesign.tk
 
Written by Cosimo Orlando for C/D.tk .
MIT License, Copyright (c) 2014, all text above must be included
in any redistribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
**************************************************************************/

#include "C_D_LCD.h"
#include <SPI.h>
#include <stdlib.h>
#include <math.h>
extern "C" {}



/*
#define CS_Write(x)		 GPIO_OUTPUT_SET(4, x)
#define TFT_CS_INIT		 PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U, FUNC_GPIO4); CS_Write(0)

#define RS_Write(x)		 GPIO_OUTPUT_SET(2, x)
#define TFT_RS_INIT 	 PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2); RS_Write(1)

#define RST_Write(x)	 GPIO_OUTPUT_SET(0, x)
#define TFT_RST_INIT	 PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0); RST_Write(0)
*/

/*******************************************************/
void C_D_LCD::initSPIM(void)
{
    TFT_CS_init();
	TFT_RS_init();
	TFT_RST_init();
	SPI.begin(HSPI);
	delay(100);
};
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

C_D_LCD::C_D_LCD(void)
{
	_width  = 0;
	_height = 0;
	initSPIM();    // initialization of SPIM.
	ResetDispaly();
}

/* This function transmits a command to the LCD driver */
void C_D_LCD::LCDCommand(uint8 datacmd)
{
	RS_Write(LOW);
	SPI.spi_tx8(datacmd);
}
/*******************************************************/

/* This function transmits a data to the LCD driver */
void C_D_LCD::LCDData(uint8 datadt)
{
	RS_Write(HIGH);
	SPI.spi_tx8(datadt);
	
}
/*******************************************************/
void C_D_LCD::initDISPLAY(void)
{
    x_start = y_start = 0u;                         // May be overridden in init function.
    
    LCDCommand(0xF0);
    LCDData(0x5A); LCDData(0x5A);                   // Excommand2.
	
    LCDCommand(0xFC);
    LCDData(0x5A); LCDData(0x5A);                   // Excommand3.
	
    LCDCommand(0x26);
    LCDData(0x01);                                  // Gamma set.
	
    LCDCommand(0xFA);
    LCDData(0x02); LCDData(0x1F); LCDData(0x00);
    LCDData(0x10); LCDData(0x22); LCDData(0x30);
    LCDData(0x38); LCDData(0x3A); LCDData(0x3A);
    LCDData(0x3A); LCDData(0x3A); LCDData(0x3A);
    LCDData(0x3D); LCDData(0x02); LCDData(0x01);	// Positive gamma control.
	
    LCDCommand(0xFB);
    LCDData(0x21); LCDData(0x00); LCDData(0x02);
    LCDData(0x04); LCDData(0x07); LCDData(0x0A);
    LCDData(0x0B); LCDData(0x0C); LCDData(0x0C);
    LCDData(0x16); LCDData(0x1E); LCDData(0x30);
    LCDData(0x3F); LCDData(0x01); LCDData(0x02);	// Negative gamma control.
	
    //////////////power setting sequence//////////
    
    LCDCommand(0xFD);
    LCDData(0x00); LCDData(0x00); LCDData(0x00);
    LCDData(0x17); LCDData(0x10); LCDData(0x00);
    LCDData(0x01); LCDData(0x01); LCDData(0x00);
    LCDData(0x1F); LCDData(0x1F);                   // Analog parameter control.
	
    LCDCommand(0xF4);
    LCDData(0x00); LCDData(0x00); LCDData(0x00);
    LCDData(0x00); LCDData(0x00); LCDData(0x3F);
    LCDData(0x3F); LCDData(0x07); LCDData(0x00);
    LCDData(0x3C); LCDData(0x36); LCDData(0x00);
    LCDData(0x3C); LCDData(0x36); LCDData(0x00);	// Power control.
	
    LCDCommand(0xF5);
    LCDData(0x00); LCDData(0x70); LCDData(0x66);
    LCDData(0x00); LCDData(0x00); LCDData(0x00);
    LCDData(0x00); LCDData(0x00); LCDData(0x00);
    LCDData(0x00); LCDData(0x6D); LCDData(0x66);
    LCDData(0x06);                                  // VCOM control.
	
    LCDCommand(0xF6);
    LCDData(0x02); LCDData(0x00); LCDData(0x3F);
    LCDData(0x00); LCDData(0x00); LCDData(0x00);
    LCDData(0x02); LCDData(0x00); LCDData(0x06);
    LCDData(0x01); LCDData(0x00);                   // Source control.
	
    /////////////initializing sequence/////////////
    
    LCDCommand(0xF2);
    LCDData(0x00); LCDData(0x01); /*04*/ LCDData(0x03);
    LCDData(0x08); LCDData(0x08); LCDData(0x04);
    LCDData(0x00); LCDData(0x00); LCDData(0x00);
    LCDData(0x00); LCDData(0x00); LCDData(0x01);
    LCDData(0x00); LCDData(0x00); LCDData(0x04);
    LCDData(0x08); LCDData(0x08);                   // Display control.
	
    LCDCommand(0xF8);
    LCDData(0x11);                                  // Gate control.
	
    LCDCommand(0xF7);
    LCDData(0xC8); LCDData(0x20); LCDData(0x00);
    LCDData(0x00);	                                // Interface control.
    
    LCDCommand(0xF3);
    LCDData(0x00);
    LCDData(0x00);	                                // Power sequence control.
	
    LCDCommand(SLEEPOUT);
    delay(50);                                    // Wake.
	
    LCDCommand(0xF3);
    LCDData(0x00); LCDData(0x01);
    delay(50);	                                // Power sequence control.
	
    LCDCommand(0xF3);
    LCDData(0x00); LCDData(0x03);
    delay(50);	                                // Power sequence control.
	
    LCDCommand(0xF3);
    LCDData(0x00); LCDData(0x07);
    delay(50);	                                // Power sequence control.
	
    LCDCommand(0xF3);
    LCDData(0x00); LCDData(0x0F);
    delay(50);	                                // Power sequence control.
	
    LCDCommand(0xF4);
    LCDData(0x00); LCDData(0x04); LCDData(0x00);
    LCDData(0x00); LCDData(0x00); LCDData(0x3F);
    LCDData(0x3F); LCDData(0x07); LCDData(0x00);
    LCDData(0x3C); LCDData(0x36); LCDData(0x00);
    LCDData(0x3C); LCDData(0x36); LCDData(0x00);
    delay(50);	                                // Power control.
	
    LCDCommand(0xF3);
    LCDData(0x00); LCDData(0x1F);
    delay(50);	                                // Power sequence control.
	
    LCDCommand(0xF3);
    LCDData(0x00); LCDData(0x7F);
    delay(50);	                                // Power sequence control.
	
    LCDCommand(0xF3);
    LCDData(0x00); LCDData(0xFF);
    delay(50);	                                // Power sequence control.
    
    LCDCommand(0xFD);
    LCDData(0x00); LCDData(0x00); LCDData(0x00);
    LCDData(0x17); LCDData(0x10); LCDData(0x00);
    LCDData(0x00); LCDData(0x01); LCDData(0x00);
    LCDData(0x16); LCDData(0x16);                   // Analog parameter control.

    LCDCommand(0xF4);
    LCDData(0x00); LCDData(0x09); LCDData(0x00);
    LCDData(0x00); LCDData(0x00); LCDData(0x3F);
    LCDData(0x3F); LCDData(0x07); LCDData(0x00);
    LCDData(0x3C); LCDData(0x36); LCDData(0x00);
    LCDData(0x3C); LCDData(0x36); LCDData(0x00);    // Power control.

    LCDCommand(MADCTL);                             // Memory access data control.
    LCDData(0x08);    
    LCDCommand(0x35);                               // Tearing effect line on.
    LCDData(NOP);
	LCDCommand(DISPON);                             // Display on.
    LCDCommand(RAMWR);                              // Memory write.
    
    _width  = WIDTH;
    _height = HEIGHT;
}
/*******************************************************/
void C_D_LCD::setAddrWindow(uint8 x0, uint8 y0, uint8 x1, uint8 y1)
{
  LCDCommand(CASET);      // column addr set
  LCDData(NOP);  
  LCDData(x0+x_start);    // XSTART
  LCDData(NOP);
  LCDData(x1+x_start);    // XEND
  LCDCommand(RASET);      // row addr set
  LCDData(NOP);
  LCDData(y0+y_start);    // YSTART
  LCDData(NOP);
  LCDData(y1+y_start);    // YEND

  LCDCommand(RAMWR);      // write to RAM
}
/*******************************************************/
void C_D_LCD::fillColor(uint32 color)
{  
  RS_Write(HIGH);
  SPI.spi_tx16(color);
}
/*******************************************************/
void C_D_LCD::drawPixel(uint16 x, uint16 y, uint32 color)
{
  if((x < 0) || (x >= _width) || (y < 0) || (y >= _height)) return;
 
  setAddrWindow(x,y,x+1,y+1);
  
  fillColor(color);
}
/*******************************************************/
void C_D_LCD::drawLine(uint16 x0, uint16 y0, uint16 x1, uint16 y1, uint32 color)
{
  uint16 steep = abs(y1 - y0) > abs(x1 - x0);
  
  if (steep) { swap(x0, y0); swap(x1, y1); }

  if (x0 > x1) { swap(x0, x1); swap(y0, y1); }

  uint16 dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  uint16 err = dx / 2;
  uint16 ystep;

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
void C_D_LCD::setWidth(uint8 d)
{
    if (d == 0) // if (d == NULL)
        _width = WIDTH;
    else
        _width = d;
}
/*******************************************************/
void C_D_LCD::setHeight(uint8 d)
{
    if (d == 0) // if (d == NULL)
        _height = HEIGHT;
    else
        _height = d;
}
/*******************************************************/
uint8 C_D_LCD::getWidth(void)
{
    return _width;
}
/*******************************************************/
uint8 C_D_LCD::getHeight(void)
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
void C_D_LCD::RotSetting(uint8 m)
{
  LCDCommand(MADCTL);
  uint8 rotation = m % 4; // can't be higher than 3
  switch (rotation)
  { 
    case 0: // portrait 0°
    LCDData(MADCTL_BGR);
    _width  = WIDTH;
    _height = HEIGHT;
    break;
    
    case 1: // landscape 90°
    LCDData(MADCTL_MX | MADCTL_MV | MADCTL_BGR);
    _width  = HEIGHT;
    _height = WIDTH;
    break;
    
    case 2: // portrait 180°
    LCDData(MADCTL_MX | MADCTL_MY | MADCTL_BGR);
    _width  = WIDTH;
    _height = HEIGHT;
    break;
    
    case 3: // landscape 270°
    LCDData(MADCTL_MY | MADCTL_MV | MADCTL_BGR);
    _width  = HEIGHT;
    _height = WIDTH;
    break;
  }
}
/*******************************************************/
void C_D_LCD::drawFastVLine(uint16 x, uint16 y, uint16 h, uint32 color)
{  
  // Rudimentary clipping
  if((x < 0) || (x >= _width) || (y < 0) || (y >= _height)) return;
  if((y+h-1) >= _height)  h = _height-y;
  
  setAddrWindow(x, y, x, y+h-1);

  while (h--) {
    fillColor(color);
  }
}
/*******************************************************/
void C_D_LCD::drawFastHLine(uint16 x, uint16 y, uint16 w, uint32 color)
{
  // Rudimentary clipping
  if((x < 0) || (x >= _width) || (y < 0) || (y >= _height)) return;
  if((x+w-1) >= _width)  w = _width-x;
  setAddrWindow(x, y, x+w-1, y);

  while (w--) {
    fillColor(color);
  }
}
/*******************************************************/
void C_D_LCD::drawRect(uint16 x, uint16 y, uint16 w, uint16 h, uint32 color)
{
  drawFastHLine(x, y, w, color);
  drawFastHLine(x, y+h-1, w, color);
  drawFastVLine(x, y, h, color);
  drawFastVLine(x+w-1, y, h, color);
}
/*******************************************************/
void C_D_LCD::fillRect(uint16 x, uint16 y, uint16 w, uint16 h, uint32 color)
{
  uint16 i;
  for (i = x; i < x+w; i++) {
    drawFastVLine(i, y, h, color);
  }
}
/*******************************************************/
void C_D_LCD::fillScreen(uint32 color)
{
  fillRect(0, 0, _width, _height, color);
}
/*******************************************************/
void C_D_LCD::lcdTest(void)
{
  uint8 i;
  for (i = 0; i < 100; i++) drawPixel(i, i, WHITE);
}
/*******************************************************/
void C_D_LCD::drawCircle(uint16 x0, uint16 y0, uint16 r, uint32 color)
{
  uint16 f = 1 - r;
  uint16 ddF_x = 1;
  uint16 ddF_y = -2 * r;
  uint16 x = 0;
  uint16 y = r;

  drawPixel(x0  , y0+r, color);
  drawPixel(x0  , y0-r, color);
  drawPixel(x0+r, y0  , color);
  drawPixel(x0-r, y0  , color);

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
void C_D_LCD::drawCircleHelper( uint16 x0, uint16 y0, uint16 r, uint8 cornername, uint32 color)
{
  uint16 f     = 1 - r;
  uint16 ddF_x = 1;
  uint16 ddF_y = -2 * r;
  uint16 x     = 0;
  uint16 y     = r;

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
void C_D_LCD::fillCircleHelper(uint16 x0, uint16 y0, uint16 r, uint8 cornername, uint16 delta, uint32 color)
{
  uint16 f     = 1 - r;
  uint16 ddF_x = 1;
  uint16 ddF_y = -2 * r;
  uint16 x     = 0;
  uint16 y     = r;

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
void C_D_LCD::fillCircle(uint16 x0, uint16 y0, uint16 r, uint32 color)
{
  drawFastVLine(x0, y0-r, 2*r+1, color);
  fillCircleHelper(x0, y0, r, 3, 0, color);
}
/*******************************************************/

/* Fill a rounded rectangle. */
void C_D_LCD::fillRoundRect(uint16 x, uint16 y, uint16 w, uint16 h, uint16 r, uint32 color)
{
  // smarter version
  fillRect(x+r, y, w-2*r, h, color);

  // draw four corners
  fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
  fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}
/*******************************************************/
char* C_D_LCD::toChar(uint8 d)
{
    character = (char)(d+48);
    if(d < 10) return &character;
    return 0;
}
/*******************************************************/
void C_D_LCD::drawChar(uint16 x, uint16 y, unsigned char c, uint32 color, uint16 bg, uint8 size)
{
  if((x >= _width)            || // Clip right
    (y  >= _height)           || // Clip bottom
    ((x + 6 * size - 1) < 0)  || // Clip left
    ((y + 8 * size - 1) < 0))    // Clip top
    return;

  int8 i;

  for (i = 0; i < 6; i++ ) {
    uint8 line;
    if (i == 5) 
      line = 0x0;
    else 
      line = font[c*5+i];
    int8 j;
    for (j = 0; j < 8; j++) {
      if (line & 0x1) {
        if (size == 1)          // default size
          drawPixel(x+i, y+j, color);
        else {                  // big size
          fillRect(x+(i*size), y+(j*size), size, size, color);
        } 
      } else if (bg != color) {
        if (size == 1)          // default size
          drawPixel(x+i, y+j, bg);
        else {                  // big size
          fillRect(x+i*size, y+j*size, size, size, bg);
        }
      }
      line >>= 1;
    }
  }
}
/*******************************************************/
void C_D_LCD::print(char* text, uint32 color, uint16 bg, uint8 size)
{
    uint8 i, j, nChar;
    i = j = 0;
    nChar = ' ';
    
    for(j = 0; j < strlen(text); j++)
    {
        if (text[j] == '\n')
        {
            j++;
            i = x_start = 0;    // x reset
            y_start += size*8;  // new line
        }
        else if (text[j] == '\r')
        {
            // skip em
        }
        
        if (_height == HEIGHT)
            nChar = 21;
        else if (_height == WIDTH)
            nChar = 26;
        
        if (i == nChar)
        {
            i = x_start = 0;
            y_start += size*8; // new line
        }
        
        x_start = i+5*i*size;
        drawChar(0, 0, text[j], color, bg, size);    
        i++;
    }
    x_start = 0;
    y_start = 0;
}
/*******************************************************/
void C_D_LCD::printN(char* textTwo, uint32 color, uint16 bg, uint8 size, uint8 num)
{
    char tempNum[1];
    char tempText[strlen(textTwo)];
    
    uint8 c = num/100;
    uint8 d = num/10 - c*10;
    uint8 u = num - c*100 - d*10;

    if ((num >= 100)&&(num <= 255))
    {
        strncat(tempNum, toChar(c), 1);
        strncat(tempNum, toChar(d), 1);
        strncat(tempNum, toChar(u), 1);
    }
    else if ((num >= 10)&&(num < 100))
    {
        strncat(tempNum, toChar(d), 1);
        strncat(tempNum, toChar(u), 1);
    }
    else
    strncat(tempNum, toChar(u), 1);

    strcpy(tempText, textTwo);
    
    strncat(tempText, tempNum, strlen(tempNum));
    print(tempText, color, bg, size);
}