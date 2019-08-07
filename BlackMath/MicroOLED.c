/******************************************************************************
MicroOLED.cpp
Biblioteca de acesso ao OLED da placa BlackMath.
Modificado por Marcellus Pereira <marcellus @laboratoriosacme.net>

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

#include <MicroOLED.h>
#include "twi.h"
#include <string.h> 
#include <stdlib.h>

#ifndef _BV
#define _BV(x) (1<<x)
#endif

// Add header of the fonts here.  Remove as many as possible to conserve FLASH memory.
#include "util/font5x7.h"
//#include "util/font8x16.h"
//#include "util/fontlargenumber.h"
//#include "util/7segment.h"
//#include "util/fontlargeletter31x48.h"

// Change the total fonts included
#ifdef INCLUDE_LARGE_LETTER_FONT
#define TOTALFONTS		2
#else
#define TOTALFONTS		1
#endif

// Add the font name as declared in the header file.  Remove as many as possible to conserve FLASH memory.
const unsigned char *fontsPointer[]={
	font5x7
//	,font8x16
//	,sevensegment
//	,fontlargenumber
#ifdef INCLUDE_LARGE_LETTER_FONT
	,fontlargeletter31x48
#endif
};

static unsigned char screenmemory [512] = { //BlackMath logo
0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x10, 0x30, 0x60, 0x30, 0x10, 0x10, 0x30, 0x20, 0xE0, 0x80,
0x80, 0xC0, 0x60, 0x20, 0x10, 0x10, 0xF0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40,
0x60, 0xA0, 0x90, 0x18, 0xE8, 0x2C, 0x64, 0xC4, 0x44, 0x24, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x40, 0x20, 0xB0, 0x10, 0x90, 0x18, 0x18, 0x10, 0x30, 0xA0,
0xB0, 0x10, 0x50, 0x10, 0xB0, 0x60, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xC0, 0x40, 0x20, 0x30, 0x10, 0x18, 0xE8, 0x2C, 0x24, 0xE4, 0x44, 0x44, 0xE4, 0x1C, 0x00, 0x00,
0x00, 0x00, 0x07, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xCE, 0xCD, 0x48, 0x8E, 0x00, 0x08, 0x1C, 0x3F,
0xFF, 0xF2, 0x7E, 0x08, 0xE7, 0x08, 0xF7, 0xFF, 0x00, 0x00, 0xF8, 0x4C, 0x76, 0xB3, 0xC1, 0x01,
0x03, 0x06, 0x1C, 0x70, 0xC0, 0xE0, 0x38, 0x4C, 0x06, 0xE2, 0x93, 0x91, 0xF1, 0x25, 0xE3, 0x93,
0xFF, 0x00, 0x00, 0x00, 0x77, 0x6B, 0x29, 0x01, 0x01, 0xE1, 0x3F, 0x0C, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7C, 0x87, 0x01, 0x00, 0x08, 0x3F, 0xC6, 0x84, 0xFE, 0x00, 0x00, 0x18, 0x3C, 0x43,
0xC7, 0x7F, 0xFE, 0x01, 0x0A, 0x11, 0x81, 0xFF, 0x00, 0xF8, 0xCC, 0x76, 0xB3, 0xE1, 0x81, 0x01,
0x02, 0x0C, 0x38, 0xC0, 0x30, 0xFC, 0x66, 0x13, 0x21, 0x81, 0x81, 0x81, 0xE1, 0x8D, 0xE9, 0x31,
0x19, 0xFF, 0x00, 0x20, 0xF0, 0x00, 0xCF, 0x64, 0xC6, 0x1B, 0x62, 0x8E, 0x19, 0xF0, 0x00, 0x00,
0x00, 0x00, 0x70, 0x5F, 0x40, 0x41, 0x51, 0x54, 0x56, 0x46, 0x44, 0x46, 0x63, 0x30, 0x18, 0x0C,
0x07, 0x07, 0xFE, 0x60, 0x63, 0xA0, 0x10, 0x09, 0x1F, 0x23, 0x48, 0x48, 0x43, 0x44, 0x24, 0x37,
0x10, 0x30, 0x48, 0x54, 0x69, 0x27, 0x10, 0x31, 0x64, 0x44, 0x5B, 0x5A, 0x43, 0x62, 0x33, 0x1F,
0x3F, 0x60, 0xC0, 0xA0, 0x16, 0xBF, 0xBC, 0xE0, 0x98, 0x31, 0x26, 0x1C, 0x30, 0xA0, 0xE0, 0x00,
0x00, 0x00, 0x00, 0x01, 0x06, 0x8C, 0xE8, 0x30, 0x90, 0x94, 0x49, 0x48, 0x50, 0x50, 0xD0, 0xAC,
0x27, 0x82, 0x51, 0x78, 0x0C, 0x06, 0x01, 0x1E, 0x33, 0x69, 0x48, 0x43, 0x44, 0x64, 0x27, 0x10,
0x30, 0x68, 0x54, 0x48, 0x23, 0x37, 0x18, 0x33, 0x2C, 0x64, 0x59, 0x5B, 0x67, 0x37, 0x1B, 0x0E,
0x06, 0x0F, 0x38, 0x40, 0x60, 0xA0, 0x97, 0x4C, 0x31, 0x9F, 0xC0, 0x65, 0x18, 0x0F, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x03, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, 0x01, 0x02, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0F,
0x0A, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0C, 0x08, 0x0C, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00
};

unsigned char foreColor,drawMode,fontWidth, fontHeight, fontType, fontStartChar, fontTotalChar, cursorX, cursorY;
unsigned int fontMapWidth;
static const unsigned char *fontsPointer[];


/** \brief Initialisation of MicroOLED Library.

    Setup IO pins for SPI port then send initialisation commands to the SSD1306 controller inside the OLED.
*/
void MicroOLED_begin(){
	// default 5x7 font
	MicroOLED_setFontType(0);
	MicroOLED_setColor(WHITE);
	MicroOLED_setDrawMode(NORM);
	MicroOLED_setCursor(0,0);

	// Display Init sequence for 64x48 OLED module
	MicroOLED_command(DISPLAYOFF);			// 0xAE
	
	MicroOLED_command(SETDISPLAYCLOCKDIV);	// 0xD5
	MicroOLED_command(0x80);					// the suggested ratio 0x80

	MicroOLED_command(SETMULTIPLEX);			// 0xA8
	MicroOLED_command(0x1F);//1f

	MicroOLED_command(SETDISPLAYOFFSET);		// 0xD3
	MicroOLED_command(0x0);					// no offset

	MicroOLED_command(SETSTARTLINE | 0x40);	// line #0

	MicroOLED_command(CHARGEPUMP);			// enable charge pump
	MicroOLED_command(0x14);

	MicroOLED_command(SEGREMAP | 0xa1);
	MicroOLED_command(COMSCANDEC);

	MicroOLED_command(SETCOMPINS);			// 0xDA
	MicroOLED_command(0x02);

	MicroOLED_command(SETCONTRAST);			// 0x81
	MicroOLED_command(0xcF);

	MicroOLED_command(SETPRECHARGE);			// 0xd9
	MicroOLED_command(0xF1);

	MicroOLED_command(SETVCOMDESELECT);			// 0xDB
	MicroOLED_command(0x40);
	
	MicroOLED_command(NORMALDISPLAY);			// 0xA6
	MicroOLED_command(DISPLAYALLONRESUME);	// 0xA4

	MicroOLED_command(DISPLAYON);				//--turn on oled panel
	MicroOLED_clear(ALL);						// Erase hardware memory inside the OLED controller to avoid random data in memory.
}

/** \brief Send the display a command byte

    Send a command via SPI, I2C or parallel	to SSD1306 controller.
	For SPI we set the DC and CS pins here, and call spiTransfer(byte)
	to send the data. For I2C and Parallel we use the write functions
	defined in hardware.cpp to send the data.
*/
void MicroOLED_command(unsigned char c) {

		// Write to our address, make sure it knows we're sending a
		// command:
		//i2cWrite(0, I2C_COMMAND, c);
		char buffer[8];
		buffer[0] = I2C_COMMAND;
		buffer[1] = c;
		
		TWI_MasterMode_Write(0x3c, buffer, 1 ,2);

}

/** \brief Send the display a data byte

    Send a data byte via SPI, I2C or parallel to SSD1306 controller.
	For SPI we set the DC and CS pins here, and call spiTransfer(byte)
	to send the data. For I2C and Parallel we use the write functions
	defined in hardware.cpp to send the data.
*/
void MicroOLED_data(unsigned char c) {

		// Write to our address, make sure it knows we're sending a
		// data byte:
		//i2cWrite(i2c_address, I2C_DATA, c);
		char buffer[8];
		buffer[0] = I2C_DATA;
		buffer[1] = c;
		
		TWI_MasterMode_Write(0x3c, buffer, 1 ,2);

}

/** \brief Set SSD1306 page address.

    Send page address command and address to the SSD1306 OLED controller.
*/
void MicroOLED_setPageAddress(unsigned char add) {
	add=0xb0|add;
	MicroOLED_command(add);
	return;
}

/** \brief Set SSD1306 column address.

    Send column address command and address to the SSD1306 OLED controller.
*/
void MicroOLED_setColumnAddress(unsigned char add) {
	//command((0x10|(add>>4))+0x02);
	MicroOLED_command(0x10|(add>>4));
	MicroOLED_command((0x0f&add));
	return;
}

/** \brief Clear screen buffer or SSD1306's memory.

    To clear GDRAM inside the LCD controller, pass in the variable mode = ALL and to clear screen page buffer pass in the variable mode = PAGE.
*/
void MicroOLED_clear(unsigned char mode) {
	int i, j;
	//	unsigned char page=6, col=0x40;
	if (mode==ALL) {
		for (i=0;i<4; i++) {
			MicroOLED_setPageAddress(i);
			MicroOLED_setColumnAddress(0);
			for (j=0; j<0x80; j++) {
				MicroOLED_data(0);
			}
		}
	}
	else
	{
		//memset(screenmemory,0,384);			// (64 x 48) / 8 = 384
		memset(screenmemory,0,512);			// (128 x 32) / 8 = 512
		//display();
	}
}

/** \brief Clear or replace screen buffer or SSD1306's memory with a character.

	To clear GDRAM inside the LCD controller, pass in the variable mode = ALL with c character and to clear screen page buffer, pass in the variable mode = PAGE with c character.
*/
void MicroOLED_clearS(unsigned char mode, unsigned char c) {
	int i, j;
	//unsigned char page=6, col=0x40;
	if (mode==ALL) {
		for (i=0;i<4; i++) {
			MicroOLED_setPageAddress(i);
			MicroOLED_setColumnAddress(0);
			for (j=0; j<0x80; j++) {
				MicroOLED_data(c);
			}
		}
	}
	else
	{
		//memset(screenmemory,c,384);			// (64 x 48) / 8 = 384
		memset(screenmemory,0,512);			// (128 x 32) / 8 = 512
		MicroOLED_display();
	}
}

/** \brief Invert display.

    The WHITE color of the display will turn to BLACK and the BLACK will turn to WHITE.
*/
void MicroOLED_invert(char inv) {
	if (inv)
	MicroOLED_command(INVERTDISPLAY);
	else
	MicroOLED_command(NORMALDISPLAY);
}

/** \brief Set contrast.

    OLED contract value from 0 to 255. Note: Contrast level is not very obvious.
*/
void MicroOLED_contrast(unsigned char contrast) {
	MicroOLED_command(SETCONTRAST);			// 0x81
	MicroOLED_command(contrast);
}

/** \brief Transfer display memory.

    Bulk move the screen buffer to the SSD1306 controller's memory so that images/graphics drawn on the screen buffer will be displayed on the OLED.
*/
void MicroOLED_display(void) {
	unsigned char i, j;

	for (i=0; i<4; i++) {
		MicroOLED_setPageAddress(i);
		MicroOLED_setColumnAddress(0);
		for (j=0;j<128;j++) {
			MicroOLED_data(screenmemory[i*128+j]);
		}
	}
}

/** \brief Override Arduino's Print.

    Arduino's print overridden so that we can use uView.print().
*/
size_t MicroOLED_write(unsigned char c) {
	if (c == '\n') {
		cursorY += fontHeight;
		cursorX  = 0;
	} else if (c == '\r') {
		// skip
	} else {
		MicroOLED_drawCharS(cursorX, cursorY, c, foreColor, drawMode);
		cursorX += fontWidth+1;
		if ((cursorX > (LCDWIDTH - fontWidth))) {
			cursorY += fontHeight;
			cursorX = 0;
		}
	}

	return 1;
}

size_t MicroOLED_writeS(const char* string) {
	unsigned char	contador = 0;
	while( (*(string+contador) != 0) && (contador < 255)){
		MicroOLED_write(*(string+contador));
		contador++;
	 }

	//	MicroOLED_write(*(string));

	return 1;
}




/** \brief Set cursor position.

MicroOLED's cursor position to x,y.
*/
void MicroOLED_setCursor(unsigned char x, unsigned char y) {
	cursorX=x;
	cursorY=y;
}

/** \brief Draw pixel.

Draw pixel using the current fore color and current draw mode in the screen buffer's x,y position.
*/
void MicroOLED_pixel(unsigned char x, unsigned char y) {
	MicroOLED_pixelS(x,y,foreColor,drawMode);
}

/** \brief Draw pixel with color and mode.

Draw color pixel in the screen buffer's x,y position with NORM or XOR draw mode.
*/
void MicroOLED_pixelS(char x, char y, char color, char mode) {
	if ((x<0) ||  (x>=LCDWIDTH) || (y<0) || (y>=LCDHEIGHT)){
		// Serial.begin(115200);
		// Serial.print("X: ");
		// Serial.println(x);
		// Serial.print("Y: ");
		// Serial.println(y);
		// Serial.flush();
		// Serial.end();
		return;
	}
	

	if (mode==XOR) {
		if (color==WHITE)
		screenmemory[x+ (y/8)*LCDWIDTH] ^= _BV((y%8));
	}
	else {
		if (color==WHITE)
		screenmemory[x+ (y/8)*LCDWIDTH] |= _BV((y%8));
		else
		screenmemory[x+ (y/8)*LCDWIDTH] &= ~_BV((y%8));
	}
}

/** \brief Draw line.

Draw line using current fore color and current draw mode from x0,y0 to x1,y1 of the screen buffer.
*/
void MicroOLED_line(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1) {
	MicroOLED_lineS(x0,y0,x1,y1,foreColor,drawMode);
}

/** \brief Draw line with color and mode.

Draw line using color and mode from x0,y0 to x1,y1 of the screen buffer.
*/
void MicroOLED_lineS( unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char color, unsigned char mode) {
	unsigned char steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		swap(x0, y0);
		swap(x1, y1);
	}

	if (x0 > x1) {
		swap(x0, x1);
		swap(y0, y1);
	}

	int dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int err = dx / 2;
	int ystep;

	if (y0 < y1) {
		ystep = 1;
	} else {
		ystep = -1;}

	for (; x0<x1; x0++) {
		if (steep) {
			MicroOLED_pixelS(y0, x0, color, mode);
		} else {
			MicroOLED_pixelS(x0, y0, color, mode);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}

/** \brief Draw horizontal line.

Draw horizontal line using current fore color and current draw mode from x,y to x+width,y of the screen buffer.
*/
void MicroOLED_lineH(unsigned char x, unsigned char y, unsigned char width) {
	MicroOLED_lineS(x,y,x+width,y,foreColor,drawMode);
}

/** \brief Draw horizontal line with color and mode.

Draw horizontal line using color and mode from x,y to x+width,y of the screen buffer.
*/
void MicroOLED_lineHS(unsigned char x, unsigned char y, unsigned char width, unsigned char color, unsigned char mode) {
	MicroOLED_lineS(x,y,x+width,y,color,mode);
}

/** \brief Draw vertical line.

Draw vertical line using current fore color and current draw mode from x,y to x,y+height of the screen buffer.
*/
void MicroOLEDlineV(unsigned char x, unsigned char y, unsigned char height) {
	MicroOLED_lineS(x,y,x,y+height,foreColor,drawMode);
}

/** \brief Draw vertical line with color and mode.

Draw vertical line using color and mode from x,y to x,y+height of the screen buffer.
*/
void MicroOLED_lineVS(unsigned char x, unsigned char y, unsigned char height, unsigned char color, unsigned char mode) {
	MicroOLED_lineS(x,y,x,y+height,color,mode);
}

/** \brief Draw rectangle.

Draw rectangle using current fore color and current draw mode from x,y to x+width,y+height of the screen buffer.
*/
void MicroOLED_rect(unsigned char x, unsigned char y, unsigned char width, unsigned char height) {
	MicroOLED_rectS(x,y,width,height,foreColor,drawMode);
}

/** \brief Draw rectangle with color and mode.

Draw rectangle using color and mode from x,y to x+width,y+height of the screen buffer.
*/
void MicroOLED_rectS(unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned char color , unsigned char mode) {
	unsigned char tempHeight;

	MicroOLED_lineHS(x,y, width, color, mode);
	MicroOLED_lineHS(x,y+height-1, width, color, mode);

	tempHeight=height-2;

	// skip drawing vertical lines to avoid overlapping of pixel that will
	// affect XOR plot if no pixel in between horizontal lines
	if (tempHeight<1) return;

	MicroOLED_lineVS(x,y+1, tempHeight, color, mode);
	MicroOLED_lineVS(x+width-1, y+1, tempHeight, color, mode);
}

/** \brief Draw filled rectangle.

Draw filled rectangle using current fore color and current draw mode from x,y to x+width,y+height of the screen buffer.
*/
void MicroOLED_rectFill(unsigned char x, unsigned char y, unsigned char width, unsigned char height) {
	MicroOLED_rectFillS(x,y,width,height,foreColor,drawMode);
}

/** \brief Draw filled rectangle with color and mode.

Draw filled rectangle using color and mode from x,y to x+width,y+height of the screen buffer.
*/
void MicroOLED_rectFillS(unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned char color , unsigned char mode) {
	int i;
	// TODO - need to optimise the memory map draw so that this function will not call pixel one by one
	for (i=x; i<x+width;i++) {
		MicroOLED_lineVS(i,y, height, color, mode);
	}
}

/** \brief Draw circle.

    Draw circle with radius using current fore color and current draw mode at x,y of the screen buffer.
*/
void MicroOLED_circle(unsigned char x0, unsigned char y0, unsigned char radius) {
	MicroOLED_circleS(x0,y0,radius,foreColor,drawMode);
}

/** \brief Draw circle with color and mode.

Draw circle with radius using color and mode at x,y of the screen buffer.
*/
void MicroOLED_circleS(unsigned char x0, unsigned char y0, unsigned char radius, unsigned char color, unsigned char mode) {
	//TODO - find a way to check for no overlapping of pixels so that XOR draw mode will work perfectly
	char f = 1 - radius;
	char ddF_x = 1;
	char ddF_y = -2 * radius;
	char x = 0;
	char y = radius;

	MicroOLED_pixelS(x0, y0+radius, color, mode);
	MicroOLED_pixelS(x0, y0-radius, color, mode);
	MicroOLED_pixelS(x0+radius, y0, color, mode);
	MicroOLED_pixelS(x0-radius, y0, color, mode);

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		MicroOLED_pixelS(x0 + x, y0 + y, color, mode);
		MicroOLED_pixelS(x0 - x, y0 + y, color, mode);
		MicroOLED_pixelS(x0 + x, y0 - y, color, mode);
		MicroOLED_pixelS(x0 - x, y0 - y, color, mode);

		MicroOLED_pixelS(x0 + y, y0 + x, color, mode);
		MicroOLED_pixelS(x0 - y, y0 + x, color, mode);
		MicroOLED_pixelS(x0 + y, y0 - x, color, mode);
		MicroOLED_pixelS(x0 - y, y0 - x, color, mode);

	}
}

/** \brief Draw filled circle.

    Draw filled circle with radius using current fore color and current draw mode at x,y of the screen buffer.
*/
void MicroOLED_circleFill(unsigned char x0, unsigned char y0, unsigned char radius) {
	MicroOLED_circleFillS(x0,y0,radius,foreColor,drawMode);
}

/** \brief Draw filled circle with color and mode.

    Draw filled circle with radius using color and mode at x,y of the screen buffer.
*/
void MicroOLED_circleFillS(unsigned char x0, unsigned char y0, unsigned char radius, unsigned char color, unsigned char mode) {
	// TODO - - find a way to check for no overlapping of pixels so that XOR draw mode will work perfectly
	int i;
	char f = 1 - radius;
	char ddF_x = 1;
	char ddF_y = -2 * radius;
	char x = 0;
	char y = radius;

	// Temporary disable fill circle for XOR mode.
	if (mode==XOR) return;

	for (i=y0-radius; i<=y0+radius; i++) {
		MicroOLED_pixelS(x0, i, color, mode);
	}

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		for (i=y0-y; i<=y0+y; i++) {
			MicroOLED_pixelS(x0+x, i, color, mode);
			MicroOLED_pixelS(x0-x, i, color, mode);
		}
		for (i=y0-x; i<=y0+x; i++) {
			MicroOLED_pixelS(x0+y, i, color, mode);
			MicroOLED_pixelS(x0-y, i, color, mode);
		}
	}
}

/** \brief Get LCD height.

    The height of the LCD return as byte.
*/
unsigned char MicroOLED_getLCDHeight(void) {
	return LCDHEIGHT;
}

/** \brief Get LCD width.

    The width of the LCD return as byte.
*/
unsigned char MicroOLED_getLCDWidth(void) {
	return LCDWIDTH;
}

/** \brief Get font width.

    The cucrrent font's width return as byte.
*/
unsigned char MicroOLED_getFontWidth(void) {
	return fontWidth;
}

/** \brief Get font height.

    The current font's height return as byte.
*/
unsigned char MicroOLED_getFontHeight(void) {
	return fontHeight;
}

/** \brief Get font starting character.

    Return the starting ASCII character of the currnet font, not all fonts start with ASCII character 0. Custom fonts can start from any ASCII character.
*/
unsigned char MicroOLED_getFontStartChar(void) {
	return fontStartChar;
}

/** \brief Get font total characters.

    Return the total characters of the current font.
*/
unsigned char MicroOLED_getFontTotalChar(void) {
	return fontTotalChar;
}

/** \brief Get total fonts.

    Return the total number of fonts loaded into the MicroOLED's flash memory.
*/
unsigned char MicroOLED_getTotalFonts(void) {
	return TOTALFONTS;
}

/** \brief Get font type.

    Return the font type number of the current font.
*/
unsigned char MicroOLED_getFontType(void) {
	return fontType;
}

/** \brief Set font type.

    Set the current font type number, ie changing to different fonts base on the type provided.
*/
unsigned char MicroOLED_setFontType(unsigned char type) {
	if ((type>=TOTALFONTS) || (type<0))
	return false;

	fontType=type;
	fontWidth=*fontsPointer[fontType];
	fontHeight=*(fontsPointer[fontType]+1);
	fontStartChar=*(fontsPointer[fontType]+2);
	fontTotalChar=*(fontsPointer[fontType]+3);
	fontMapWidth = *(fontsPointer[fontType]+4)*100 + *(fontsPointer[fontType]+5); // two bytes values into integer 16
	return true;
}

/** \brief Set color.

    Set the current draw's color. Only WHITE and BLACK available.
*/
void MicroOLED_setColor(unsigned char color) {
	foreColor=color;
}

/** \brief Set draw mode.

    Set current draw mode with NORM or XOR.
*/
void MicroOLED_setDrawMode(unsigned char mode) {
	drawMode=mode;
}

/** \brief Draw character.

    Draw character c using current color and current draw mode at x,y.
*/
void  MicroOLED_drawChar(unsigned char x, unsigned char y, unsigned char c) {
	MicroOLED_drawCharS(x,y,c,foreColor,drawMode);
}

/** \brief Draw character with color and mode.

    Draw character c using color and draw mode at x,y.
*/
void  MicroOLED_drawCharS(unsigned char x, unsigned char y, unsigned char c, unsigned char color, unsigned char mode) {
	// TODO - New routine to take font of any height, at the moment limited to font height in multiple of 8 pixels

	unsigned char rowsToDraw,row, tempC;
	unsigned char i,j,temp;
	uint16_t charPerBitmapRow,charColPositionOnBitmap,charRowPositionOnBitmap,charBitmapStartPosition;

	if ((c<fontStartChar) || (c>(fontStartChar+fontTotalChar-1)))		// no bitmap for the required c
	return;

	tempC=c-fontStartChar;

	// each row (in datasheet is call page) is 8 bits high, 16 bit high character will have 2 rows to be drawn
	rowsToDraw=fontHeight/8;	// 8 is LCD's page size, see SSD1306 datasheet
	if (rowsToDraw<=1) rowsToDraw=1;

	// the following draw function can draw anywhere on the screen, but SLOW pixel by pixel draw
	if (rowsToDraw==1) {
		for  (i=0;i<fontWidth+1;i++) {
			if (i==fontWidth) // this is done in a weird way because for 5x7 font, there is no margin, this code add a margin after col 5
			temp=0;
			else
			temp=*(fontsPointer[fontType]+FONTHEADERSIZE+(tempC*fontWidth)+i);

			for (j=0;j<8;j++) {			// 8 is the LCD's page height (see datasheet for explanation)
				if (temp & 0x1) {
					MicroOLED_pixelS(x+i, y+j, color,mode);
				}
				else {
					MicroOLED_pixelS(x+i, y+j, !color,mode);
				}

				temp >>=1;
			}
		}
		return;
	}

	// font height over 8 bit
	// take character "0" ASCII 48 as example
	charPerBitmapRow=fontMapWidth/fontWidth;  // 256/8 =32 char per row
	charColPositionOnBitmap=tempC % charPerBitmapRow;  // =16
	charRowPositionOnBitmap = (int)(tempC/charPerBitmapRow); // =1
	charBitmapStartPosition=(charRowPositionOnBitmap * fontMapWidth * (fontHeight/8)) + (charColPositionOnBitmap * fontWidth) ;

	// each row on LCD is 8 bit height (see datasheet for explanation)
	for(row=0;row<rowsToDraw;row++) {
		for (i=0; i<fontWidth;i++) {
			temp=*(fontsPointer[fontType]+FONTHEADERSIZE+(charBitmapStartPosition+i+(row*fontMapWidth)));
			for (j=0;j<8;j++) {			// 8 is the LCD's page height (see datasheet for explanation)
				if (temp & 0x1) {
					MicroOLED_pixelS(x+i,y+j+(row*8), color, mode);
				}
				else {
					MicroOLED_pixelS(x+i,y+j+(row*8), !color, mode);
				}
				temp >>=1;
			}
		}
	}

}

/** \brief Stop scrolling.

    Stop the scrolling of graphics on the OLED.
*/
void MicroOLED_scrollStop(void){
	MicroOLED_command(DEACTIVATESCROLL);
}

/** \brief Right scrolling.

Set row start to row stop on the OLED to scroll right. Refer to http://learn.microview.io/intro/general-overview-of-microview.html for explanation of the rows.
*/
void MicroOLED_scrollRight(unsigned char start, unsigned char stop){
	if (stop<start)		// stop must be larger or equal to start
	return;
	MicroOLED_scrollStop();		// need to disable scrolling before starting to avoid memory corrupt
	MicroOLED_command(RIGHTHORIZONTALSCROLL);
	MicroOLED_command(0x00);
	MicroOLED_command(start);
	MicroOLED_command(0x7);		// scroll speed frames , TODO
	MicroOLED_command(stop);
	MicroOLED_command(0x00);
	MicroOLED_command(0xFF);
	MicroOLED_command(ACTIVATESCROLL);
}

/** \brief Vertical flip.

Flip the graphics on the OLED vertically.
*/
void MicroOLED_flipVertical(int flip) {
	if (flip) {
		MicroOLED_command(COMSCANINC);
	}
	else {
		MicroOLED_command(COMSCANDEC);
	}
}

/** \brief Horizontal flip.

    Flip the graphics on the OLED horizontally.
*/
void MicroOLED_flipHorizontal(char flip) {
	if (flip) {
		MicroOLED_command(SEGREMAP | 0x0);
	}
	else {
		MicroOLED_command(SEGREMAP | 0x1);
	}
}

/*
	Return a pointer to the start of the RAM screen buffer for direct access.
*/
unsigned char *MicroOLED_getScreenBuffer(void) {
	return screenmemory;
}

/*
Draw Bitmap image on screen. The array for the bitmap can be stored in the Arduino file, so user don't have to mess with the library files.
To use, create unsigned char array that is 64x48 pixels (384 bytes). Then call .drawBitmap and pass it the array.
*/
void MicroOLED_drawBitmap(unsigned char * bitArray)
{
	int i;
  for (i=0; i<(LCDWIDTH * LCDHEIGHT / 8); i++)
    screenmemory[i] = bitArray[i];
}
