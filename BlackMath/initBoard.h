/// Definições e protótipos para configuração da BlackMath
//
//
///Author: Marcellus Pereira <marcellus@laboratoriosacme.net
///Date: 21/10/2018
///version: 1.0
//
//

#ifndef	__INITIBOARD_H__
#define __INITBOARD_H__

#include <cdefBF592-A.h>
#include <ccblkfn.h>
#include <bfrom.h>


void initBoard(void);



// Define clock
//Oscilador externo (CLKIN): 24,576MHz
//PLLDIV (Multiplicador do clock externo)	= 16
//VCO (Oscilador interno de referência)		= 393,216MHz
//CCLK (clock das instruções)	(/2)		= 196,608MHz
//SCLK (clock dos periféricos) 	(/4)		= 98,304MHz
// Veja página 10 do datasheet (https://www.analog.com/media/en/technical-documentation/data-sheets/ADSP-BF592.pdf)


#define VRCTL_VALUE         0x7000 // pino EXTCLK leva 24,576MHz para o CODEC
#define PLLCTL_VALUE        0x2000 // multiplica CLKIN por 16
#define PLLDIV_VALUE        0x001F
#define PLLLOCKCNT_VALUE    0x0000
#define PLLSTAT_VALUE       0x0000
#define RSICLK_DIV          0x0001
	



#endif

