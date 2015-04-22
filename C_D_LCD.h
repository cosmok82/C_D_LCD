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
#define BLACK	    0x000000u
#define NAVY        0x000080u
#define BLUE        0x0000FCu
#define TEAL        0x008080u
#define EMERALD	    0x50C878u
#define	GREEN       0x00FC00u
#define CYAN        0x008888u
#define SLATE 	    0u
#define INDIGO      0u
#define TURQUOISE   0u
#define OLIVE 		0u
#define MAROON 		0u
#define PURPLE 		0u
#define GRAY        0u
#define SKYBLUE		0u
#define BROWN		0u
#define CRIMSON 	0u
#define ORCHID 		0u
#define RED         0xFC0000u
#define MAGENTA     0xFC54A0u
#define ORANGE 		0u
#define PINK		0u
#define CORAL 		0u
#define SALMON 		0u
#define GOLD 		0u
#define YELLOW      0x00FCFCu
#define WHITE       0xFCFCFCu

//********************************************************************
//					    Various Definitions
////******************************************************************

#ifndef LOW
#define LOW  0u
#endif
#ifndef HIGH
#define HIGH 1u
#endif

//********************************************************************
//					      Code Definitions
////******************************************************************

#define swap(a, b) { uint16 t = a; a = b; b = t; }

//*******************************************************

class C_D_LCD { //only for ARDUINO ESP8266
	public:
	  
	  // Initialize the SPI library
	  C_D_LCD(void);
	  // Disable the SPI bus
	  /*~C_D_LCD(void);*/
	  	  
	  uint8 x_start, y_start;
	  
	  void LCDCommand(uint8 datacmd),
		   LCDData(uint8 datadt),
	  
		   initDISPLAY(void),

		   setAddrWindow(uint8 x0, uint8 y0, uint8 x1, uint8 y1),
		   fillColor(uint32 color),
		   drawPixel(uint16 x, uint16 y, uint32 color),
		   drawLine(uint16 x0, uint16 y0, uint16 x1, uint16 y1, uint32 color),
		   setWidth(uint8 d),
		   setHeight(uint8 d),
		   RotSetting(uint8 m),
		   drawFastVLine(uint16 x, uint16 y, uint16 h, uint32 color),
		   drawFastHLine(uint16 x, uint16 y, uint16 w, uint32 color),
		   drawRect(uint16 x, uint16 y, uint16 w, uint16 h, uint32 color),
		   fillRect(uint16 x, uint16 y, uint16 w, uint16 h, uint32 color),
		   fillScreen(uint32 color),
		   lcdTest(void),
		   drawCircle(uint16 x0, uint16 y0, uint16 r, uint32 color),
		   drawCircleHelper( uint16 x0, uint16 y0, uint16 r, uint8 cornername, uint32 color),
		   fillCircleHelper(uint16 x0, uint16 y0, uint16 r, uint8 cornername, uint16 delta, uint32 color),
		   fillCircle(uint16 x0, uint16 y0, uint16 r, uint32 color),
		   fillRoundRect(uint16 x, uint16 y, uint16 w, uint16 h, uint16 r, uint32 color), 
		   drawChar(uint16 x, uint16 y, unsigned char c, uint32 color, uint16 bg, uint8 size),
		   print(char* text, uint32 color, uint16 bg, uint8 size),
		   printN(char* text, uint32 color, uint16 bg, uint8 size, uint8 num);
	  char* toChar(uint8 d);
	  uint8 getWidth(void),
			getHeight(void);
	  
	private:
	  void initSPIM(void),
		   ResetDispaly(void);
	  
	  inline static void CS_Write (uint32 bit_value) { gpio_output_set((uint32) bit_value<<4, ((uint32) (~bit_value)&0x01)<<4, (uint32) 1<<4,(uint32) 0); };
	  inline static void RS_Write (uint32 bit_value) { gpio_output_set((uint32) bit_value<<2, ((uint32) (~bit_value)&0x01)<<2, (uint32) 1<<2,(uint32) 0); };
	  inline static void RST_Write(uint32 bit_value) { gpio_output_set((uint32) bit_value,    ((uint32)    (~bit_value)&0x01), (uint32)    1,(uint32) 0); };
	  inline static void TFT_CS_init(void)  { PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U, FUNC_GPIO4); CS_Write(0); };
	  inline static void TFT_RS_init(void)  { PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2); RS_Write(1); };
	  inline static void TFT_RST_init(void) { PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0); RST_Write(0);};
	  
	  uint8 _width,
			_height;
	  char character = ' ';
};

#endif // _C_D_LCD_H_INCLUDED