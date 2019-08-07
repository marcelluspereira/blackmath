/*******************************************************************
TWI / I2C
*******************************************************************/

#ifndef	__TWI_H__
#define __TWI_H__
#include <cdefBF592-A.h>


/*******************************************************************
*  definições
*******************************************************************/
#define PRESCALE_VALUE 10		/* PRESCALE = 98,304/10 = 10 */
#define RESET_TWI 0				/* RESET_TWI value for controller */
#define CLKDIV_HI 2			/* SCL high period */
#define CLKDIV_LO 3			/* SCL low period */


/*******************************************************************
*  protótipos
*******************************************************************/
void Reset_TWI(void);
void TWI_MasterMode_Write(unsigned short, unsigned char*, unsigned short, unsigned short);
void TWI_MasterMode_Read(unsigned short, unsigned char*, unsigned short);


#endif

