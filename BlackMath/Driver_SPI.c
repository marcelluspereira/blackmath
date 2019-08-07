// Rotinas de acesso à SPI
//
static void spi1_init(void)
{
	/*****************************************************************************
	 * Inicializa porta SPI1
	 * 
	 * SPI1 				-	SGTL5000 CODEC
	 * PF9 (\SPI0_SSEL3)	-	\CODEC_CS
	 * PG8 (SPI1_SCK)		- 	SCK
	 * PG9 (SPI1_MOSI)		- 	MOSI
	 * PG10 (SPI1_MISO)		- 	MISO
	 ****************************************************************************/
	*pPORTF_FER   &= ~PF9;
	*pPORTFIO_SET  = PF9;
	*pPORTFIO_DIR |= PF9;
	/* SPI SCK, MOSI, MISO */
    *pPORTG_FER   |= PG8 | PG9 | PG10;
    *pPORTG_MUX   &= ~(PG8 | PG9 | PG10);
	/* INIT */
	*pSPI1_BAUD    = 2;	/* 25MHz(MAX) */
	*pSPI1_CTL     = SPE | MSTR | EMISO | TDBR_CORE;
	*pSPI1_FLG     = 0;
	ssync();
}

/* Controla \CS do CODEC
SPI1_SSEL3 é usado como saída para controle do CODEC
*/
static void spi1_codec_cs(int estado)
{
	if(estado){
		*pPORTFIO_SET = PF8;
	}
	else{
		*pPORTFIO_CLEAR = PF8;
	}
	ssync();
}

/* SPI 1 byte transfer */
static uint8_t spi1_xfer(uint8_t send_data){
	/* Start tx */
	*pSPI0_TDBR = send_data;
	ssync();
	/* Wait until finish */
	while((*pSPI0_STAT & RXS) == 0) ssync();

	/* Return received data */
	return *pSPI0_RDBR;
}