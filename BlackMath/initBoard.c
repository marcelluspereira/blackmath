/// Rotinas de inicialiação placa
//
//
///Author: Marcellus Pereira <marcellus@laboratoriosacme.net
///Date: 21/10/2018
///version: 1.0
//
//
#include "initBoard.h"


void initBoard(void){
	// ----------------------------------------------------------  Inicializa PLL
	unsigned int SIC_IWR1_reg;                /* backup SIC_IWR1 register */

	/* use Blackfin ROM SysControl() to change the PLL */
    ADI_SYSCTRL_VALUES sysctrl ={	VRCTL_VALUE,
									PLLCTL_VALUE,		/* (24,576MHz CLKIN x (MSEL=16))::CCLK = 393,216MHz */
									PLLDIV_VALUE,		/* (393,216MHz/(SSEL=4))::SCLK = 98,304MHz */
									PLLLOCKCNT_VALUE,
									PLLSTAT_VALUE };

	/* use the ROM function */
	bfrom_SysControl( SYSCTRL_WRITE | SYSCTRL_PLLCTL | SYSCTRL_PLLDIV, &sysctrl, NULL);
	
	// ----------------------------------------------------  Inicializa TWI (I2C)
	
	
	
	
	
	// ----------------------------------------------------  Configura LED
	*pPORTF_FER		&= ~PF10;	/* Setup for LEDs */
	// Configura PF10 como saída (LED)
	*pPORTFIO_DIR |= PF10;
	
	
}

