/*****************************************************************************
 * BlackMath.c
 *****************************************************************************/

#include <cdefBF592-A.h>
#include <fract.h>
#include <cycles.h>
#include <cycle_count.h>
#include "twi.h"
#include "initBoard.h"
#include "MicroOLED.h"
#include "teste_fir/voice2_8kfs_16bit.h"
#include "teste_fir/filtro1.h"
#include <filter.h>

#define PERFORMANCE_MONITOR

int main( void )
{
	int i, n;
	cycle_stats_t stats;
	fract16 y, sample[100], delay[100], saida[NSAMPLES];
	cycle_t PM_StartCycles;
	cycle_t PM_EndCycles;
	cycle_t PM_TotalCycles;
	char texto[26] ={0};
	fract16 *pVoice;
	
	initBoard();
	
	Reset_TWI();
	MicroOLED_begin();
	MicroOLED_display();
	
	for(i=0; i<90000000; i++){
		{asm("NOP;");}
	}
		
	MicroOLED_clear(PAGE);
  	MicroOLED_rectFill(0,0,127,31);
  	MicroOLED_display();
  	
  	
  	//Fim da inicialização
  	
  	
  	//Primeiro teste ---------------------------------------------------------
  	MicroOLED_clear(PAGE);     // Clear the screen
  	MicroOLED_setFontType(0);  // Set font to type 0
  	MicroOLED_setCursor(0, 0); // Set cursor to top-left

  	MicroOLED_writeS("INICIANDO filtro 1...");
  	MicroOLED_display();
  	

  	//Zera vetor de amostras
  	//
  	for(i=0; i<NSAMPLES; i++){
  		sample[i] = 0;
  	}
  	
  	//------ Performance monitor
	#ifdef PERFORMANCE_MONITOR
	START_CYCLE_COUNT(PM_StartCycles);
	#endif
	//------ Performance monitor
  	
  	for(i=0; i<NSAMPLES; i++){
  		//zera saída do filtro
	    y=0; 

	    //lê dado do arquivo
		sample[0] = voice2[i];

	     //Convolução e acumulação
	     for (n=0; n<100; n++){
	     	y = add_fr1x16( mult_fr1x16(filtroFIR8kfsPB1kHz2kHz[n],sample[n]), y );
	     }

	     //desloca amostra
	     for (n=100-1; n>0; n--){
             sample[n]=sample[n-1];
         }
		 saida[i] = (short) y;

	     //escreve na memória de saída
	     //fwrite(&saida,sizeof(short),1,out_file);
  	 }

  	
	//------ Performance monitor
	#ifdef PERFORMANCE_MONITOR
	STOP_CYCLE_COUNT(PM_EndCycles,PM_StartCycles);		// get processing usage cycles
	#endif
	//------ Performance monitor
  	
	snprintf(texto,26,"Ciclos: %d",PM_EndCycles);
	MicroOLED_writeS(texto);
	MicroOLED_display();
 
  	for(i=0; i<90000000; i++){
		{asm("NOP;");}
	}
	//---------------------------------------------------------	Primeiro teste
	
	
	//Segundo teste ---------------------------------------------------------
  	MicroOLED_clear(PAGE);     // Clear the screen
  	MicroOLED_setFontType(0);  // Set font to type 0
  	MicroOLED_setCursor(0, 0); // Set cursor to top-left

  	MicroOLED_writeS("Iniciando filtro 2...");
  	MicroOLED_display();
  	
  	fir_state_fr16 state;
  	for(i=0; i<100; i++){
  		delay[i] = 0;
  	}
  	
  	//------ Performance monitor
	#ifdef PERFORMANCE_MONITOR
	START_CYCLE_COUNT(PM_StartCycles);
	#endif
	//------ Performance monitor
	
	
	
  	fir_init(state, filtroFIR8kfsPB1kHz2kHz, delay, 99, 0);
  	fir_fr16(voice2, saida, NSAMPLES, &state);
  	
  	
  	
  	//------ Performance monitor
	#ifdef PERFORMANCE_MONITOR
	STOP_CYCLE_COUNT(PM_EndCycles,PM_StartCycles);		// get processing usage cycles
	#endif
	//------ Performance monitor
  	
	snprintf(texto,26,"Ciclos: %d",PM_EndCycles);
	MicroOLED_writeS(texto);
	MicroOLED_display();
 
	 	
  	for(i=0; i<9000000; i++){
		{asm("NOP;");}
	}
  	
 	
  	
	while(1){
		//Zera pino PF10
		*pPORTFIO_CLEAR = PF10;
	
		for(i=0; i<9000000; i++){
			{asm("NOP;");}
		}
		//Seta pino PF10
		*pPORTFIO_SET = PF10;
		for(i=0; i<9000000; i++){
			{asm("NOP;");}
		}
	}	
	
	return 0;
}

