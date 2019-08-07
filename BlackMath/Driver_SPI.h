// Rotinas de acesso à SPI
//

#define SPI_ENABLE	1
#define SPI_DISABLE	0
static void spi1_init(void);
static void spi1_codec_cs(int estado);
static uint8_t spi1_xfer(uint8_t send_data);
