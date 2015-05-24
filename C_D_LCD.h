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

#ifndef _C_D_LCD_H_INCLUDED
#define _C_D_LCD_H_INCLUDED

#include <Arduino.h>
#include <SPI.h>
extern "C" {  //used "external C" to solve all compiling problems
#include "glcdfont.h"
#include "gpio.h"
}

#ifndef NULL
#define NULL ((void *)0)
#endif

//********************************************************************
//					LCD Dimension Definitions
////******************************************************************
#define WIDTH	128
#define HEIGHT	160

//********************************************************************
//					ST7735 Controller Definitions
////******************************************************************
//LCD Commands
#define	NOP         0x00u	// No operation
#define SWRESET     0x01u   // Software Reset
#define RDDID       0x04u
#define RDDST       0x09u
#define SLEEPIN     0x10u	// Sleep in
#define	SLEEPOUT	0x11u	// Sleep out
#define	NORON		0x13u	// Normal display mode on
#define	INVOFF		0x20u	// Display inversion off
#define INVON      	0x21u	// Display inversion on
#define	SETCON		0x25u	// Set contrast
#define DISPOFF     0x28u	// Display off
#define DISPON      0x29u	// Display on
#define CASET       0x2Au	// Column address set
#define RASET       0x2Bu	// Page address set
#define RAMWR       0x2Cu	// Memory write
#define RAMRD       0x2Eu   // Memory read
#define PTLAR       0x30u
#define	COLMOD		0x3Au	// Interface pixel format
#define	MADCTL		0x36u	// Memory data access control
#define FRMCTR1     0xB1u
#define FRMCTR2     0xB2u
#define FRMCTR3     0xB3u
#define INVCTR      0xB4u
#define DISSET5     0xB6u
#define PWCTR1      0xC0u   // Internal or external oscillator
#define PWCTR2      0xC1u
#define PWCTR3      0xC2u
#define PWCTR4      0xC3u
#define PWCTR5      0xC4u
#define PWCTR6      0xFCu
#define VMCTR1      0xC5u
#define RDID1       0xDAu
#define RDID2       0xDBu
#define RDID3       0xDCu
#define RDID4       0xDDu
#define GMCTRP1     0xE0u
#define GMCTRN1     0xE1u

//*******************************************************
//					16-Bit Color Definitions
////*****************************************************
#define BLACK	  0x000000u
#define NAVY      0x000080u
#define BLUE      0x0000FCu
#define TEAL      0x008080u
#define EMERALD	  0x50C878u
#define GREEN     0x00FC00u
#define CYAN      0x008888u
#define SLATE 	  0u
#define INDIGO    0u
#define TURQUOISE 0u
#define OLIVE 	  0u
#define MAROON 	  0u
#define PURPLE 	  0u
#define GRAY      0u
#define SKYBLUE	  0u
#define BROWN	  0u
#define CRIMSON   0u
#define ORCHID 	  0u
#define RED       0xFC0000u
#define MAGENTA   0xFC54A0u
#define ORANGE 	  0u
#define PINK	  0u
#define CORAL 	  0u
#define SALMON 	  0u
#define GOLD 	  0u
#define YELLOW    0x00FCFCu
#define WHITE     0xFCFCFCu

////////////////////////////////////////////////////////////////////////////////
//
// Various Definitions
//				 
////////////////////////////////////////////////////////////////////////////////
#ifndef LOW
#define LOW  0u
#endif
#ifndef HIGH
#define HIGH 1u
#endif

////////////////////////////////////////////////////////////////////////////////
//
// Code Definitions
//				 
////////////////////////////////////////////////////////////////////////////////
#define swap(a, b) { uint16_t t = a; a = b; b = t; }

class C_D_LCD { //only for ARDUINO ESP8266
public:
	  
  // Initialize the C_D_LCD library
  void begin(void),
	   end(void);
	  	  
  uint8_t x_start, y_start;
  
  void LCDCommand(uint8_t datacmd),
	   LCDData(uint8_t datadt),
	  
	   initDISPLAY(void),

	   setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1),
	   fillColor(uint32_t color),
	   drawPixel(uint16_t x, uint16_t y, uint32_t color),
	   drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color),
	   setWidth(uint8_t d),
	   setHeight(uint8_t d),
	   RotSetting(uint8_t m),
	   drawFastVLine(int16_t x, int16_t y, int16_t h, uint32_t color),
	   drawFastHLine(int16_t x, int16_t y, int16_t w, uint32_t color),
	   drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color),
	   fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color),
	   fillScreen(uint32_t color),
	   lcdTest(void),
	   drawCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color),
	   drawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint32_t color),
	   fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint32_t color),
	   fillCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color),
	   fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint32_t color),
	   drawChar(int16_t x, int16_t y, unsigned char c, uint32_t color, uint16_t bg, uint8_t size),
	   print(char* text, uint32_t color, uint16_t bg, uint8_t size),
	   printN(char* text, uint32_t color, uint16_t bg, uint8_t size, uint8_t num);
	
 char* toChar(uint8_t d);
 uint8_t getWidth(void),
	     getHeight(void);
	  
private:
	
  void initSPIM(void),
	   ResetDispaly(void);
	
	   #define TFT_RS_init()        pinMode(2, OUTPUT)
       #define RS_Write(bit_value)  digitalWrite(2, bit_value)
	   #define TFT_RST_init()       pinMode(16, OUTPUT)
       #define RST_Write(bit_value) digitalWrite(16, bit_value)	
  uint8_t _width,
	      _height;
  char character = ' ';
	  
};


extern C_D_LCD SPILCD;

#endif // _C_D_LCD_H_INCLUDED