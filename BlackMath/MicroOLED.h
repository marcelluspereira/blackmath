/****************************************************************************** 
MicroOLED.h
Arquivo de cabeçalho para o display OLED da placa BlackMath.
Modificado por Marcellus Pereira <marcellus @laboratoriosacme.net>

Baseado no trabalho original de:

Jim Lindblom @ SparkFun Electronics
October 26, 2014
https://github.com/sparkfun/Micro_OLED_Breakout/tree/master/Firmware/Arduino/libraries/SFE_MicroOLED

Modified by:
Emil Varughese @ Edwin Robotics Pvt. Ltd.
July 27, 2015
https://github.com/emil01/SparkFun_Micro_OLED_Arduino_Library/


This code was heavily based around the MicroView library, written by GeekAmmo
(https://github.com/geekammo/MicroView-Arduino-Library), and released under 
the terms of the GNU General Public License as published by the Free Software 
Foundation, either version 3 of the License, or (at your option) any later 
version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#ifndef	__MICROOLED_H__
#define __MICROOLED_H__


#include <stdio.h>

#define swap(a, b) { unsigned char t = a; a = b; b = t; }

#define I2C_ADDRESS_SA0_0 0b0111100
#define I2C_ADDRESS_SA0_1 0b0111101
#define I2C_COMMAND 0x00
#define I2C_DATA 0x40

#define BLACK 0
#define WHITE 1

#define LCDWIDTH			128
#define LCDHEIGHT			32
#define FONTHEADERSIZE		6

#define NORM				0
#define XOR					1

#define PAGE				0
#define ALL					1

#define WIDGETSTYLE0			0
#define WIDGETSTYLE1			1
#define WIDGETSTYLE2			2

#define SETCONTRAST 		0x81
#define DISPLAYALLONRESUME 	0xA4
#define DISPLAYALLON 		0xA5
#define NORMALDISPLAY 		0xA6
#define INVERTDISPLAY 		0xA7
#define DISPLAYOFF 			0xAE
#define DISPLAYON 			0xAF
#define SETDISPLAYOFFSET 	0xD3
#define SETCOMPINS 			0xDA
#define SETVCOMDESELECT		0xDB
#define SETDISPLAYCLOCKDIV 	0xD5
#define SETPRECHARGE 		0xD9
#define SETMULTIPLEX 		0xA8
#define SETLOWCOLUMN 		0x00
#define SETHIGHCOLUMN 		0x10
#define SETSTARTLINE 		0x40
#define MEMORYMODE 			0x20
#define COMSCANINC 			0xC0
#define COMSCANDEC 			0xC8
#define SEGREMAP 			0xA0
#define CHARGEPUMP 			0x8D
#define EXTERNALVCC 		0x01
#define SWITCHCAPVCC 		0x02

// Scroll
#define ACTIVATESCROLL 					0x2F
#define DEACTIVATESCROLL 				0x2E
#define SETVERTICALSCROLLAREA 			0xA3
#define RIGHTHORIZONTALSCROLL 			0x26
#define LEFT_HORIZONTALSCROLL 			0x27
#define VERTICALRIGHTHORIZONTALSCROLL	0x29
#define VERTICALLEFTHORIZONTALSCROLL	0x2A

typedef enum CMD {
	CMD_CLEAR,			//0
	CMD_INVERT,			//1
	CMD_CONTRAST,		//2
	CMD_DISPLAY,		//3
	CMD_SETCURSOR,		//4
	CMD_PIXEL,			//5
	CMD_LINE,			//6
	CMD_LINEH,			//7
	CMD_LINEV,			//8
	CMD_RECT,			//9
	CMD_RECTFILL,		//10
	CMD_CIRCLE,			//11
	CMD_CIRCLEFILL,		//12
	CMD_DRAWCHAR,		//13
	CMD_DRAWBITMAP,		//14
	CMD_GETLCDWIDTH,	//15
	CMD_GETLCDHEIGHT,	//16
	CMD_SETCOLOR,		//17
	CMD_SETDRAWMODE		//18
} commCommand_t;

typedef enum COMM_MODE{
	MODE_SPI,
	MODE_I2C,
	MODE_PARALLEL
} micro_oled_mode;



void MicroOLED_begin(void);
//	virtual size_t write(unsigned char);
//	virtual size_t write(const char *str);

// RAW LCD functions
void MicroOLED_command(unsigned char c);
void MicroOLED_data(unsigned char c);
void MicroOLED_setColumnAddress(unsigned char add);
void MicroOLED_setPageAddress(unsigned char add);
	
// LCD Draw functions
void MicroOLED_clear(unsigned char mode);
void MicroOLED_clearS(unsigned char mode, unsigned char c);
void MicroOLED_invert(char inv);
void MicroOLED_contrast(unsigned char contrast);
void MicroOLED_display(void);
void MicroOLED_setCursor(unsigned char x, unsigned char y);
void MicroOLED_pixel(unsigned char x, unsigned char y);
void MicroOLED_pixelS(char x, char y, char color, char mode);
void MicroOLED_line(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1);
void MicroOLED_lineS(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char color, unsigned char mode);
void MicroOLED_lineH(unsigned char x, unsigned char y, unsigned char width);
void MicroOLED_lineHS(unsigned char x, unsigned char y, unsigned char width, unsigned char color, unsigned char mode);
void MicroOLED_lineV(unsigned char x, unsigned char y, unsigned char height);
void MicroOLED_lineVS(unsigned char x, unsigned char y, unsigned char height, unsigned char color, unsigned char mode);
void MicroOLED_rect(unsigned char x, unsigned char y, unsigned char width, unsigned char height);
void MicroOLED_rectS(unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned char color , unsigned char mode);
void MicroOLED_rectFill(unsigned char x, unsigned char y, unsigned char width, unsigned char height);
void MicroOLED_rectFillS(unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned char color , unsigned char mode);
void MicroOLED_circle(unsigned char x, unsigned char y, unsigned char radius);
void MicroOLED_circleS(unsigned char x, unsigned char y, unsigned char radius, unsigned char color, unsigned char mode);
void MicroOLED_circleFill(unsigned char x0, unsigned char y0, unsigned char radius);
void MicroOLED_circleFillS(unsigned char x0, unsigned char y0, unsigned char radius, unsigned char color, unsigned char mode);
void MicroOLED_drawChar(unsigned char x, unsigned char y, unsigned char c);
void MicroOLED_drawCharS(unsigned char x, unsigned char y, unsigned char c, unsigned char color, unsigned char mode);
void MicroOLED_drawBitmap(unsigned char * bitArray);
unsigned char MicroOLED_getLCDWidth(void);
unsigned char MicroOLED_getLCDHeight(void);
void MicroOLED_setColor(unsigned char color);
void MicroOLED_setDrawMode(unsigned char mode);
unsigned char *MicroOLED_getScreenBuffer(void);

// Font functions
unsigned char MicroOLED_getFontWidth(void);
unsigned char MicroOLED_getFontHeight(void);
unsigned char MicroOLED_getTotalFonts(void);
unsigned char MicroOLED_getFontType(void);
unsigned char MicroOLED_setFontType(unsigned char type);
unsigned char MicroOLED_getFontStartChar(void);
unsigned char MicroOLED_getFontTotalChar(void);

// LCD Rotate Scroll functions	
void MicroOLED_scrollRight(unsigned char start, unsigned char stop);
void MicroOLED_scrollLeft(unsigned char start, unsigned char stop);
void MicroOLED_scrollVertRight(unsigned char start, unsigned char stop);
void MicroOLED_scrollVertLeft(unsigned char start, unsigned char stop);
void MicroOLED_scrollStop(void);
void MicroOLED_flipVertical(int flip);
void MicroOLED_flipHorizontal(char flip);

#endif
