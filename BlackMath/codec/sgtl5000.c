/*
	SGTL5000 driver for Blackfin
	author: Marcellus Pereira marcellus@laboratoriosacme.net
	date: 12/11/2018
	
	based on:
	sgtl5000.c  --  SGTL5000 ALSA SoC Audio driver
	SPDX-License-Identifier: GPL-2.0
	Copyright 2010-2011 Freescale Semiconductor, Inc. All Rights Reserved.
	*/
	
#include "sgtl5000.h"

/* default value of sgtl5000 registers */
static const struct reg_default sgtl5000_reg_defaults[] = {
	{ SGTL5000_CHIP_DIG_POWER,		0x0000 },
	{ SGTL5000_CHIP_I2S_CTRL,		0x0010 },
	{ SGTL5000_CHIP_SSS_CTRL,		0x0010 },
	{ SGTL5000_CHIP_ADCDAC_CTRL,		0x020c },
	{ SGTL5000_CHIP_DAC_VOL,		0x3c3c },
	{ SGTL5000_CHIP_PAD_STRENGTH,		0x015f },
	{ SGTL5000_CHIP_ANA_ADC_CTRL,		0x0000 },
	{ SGTL5000_CHIP_ANA_HP_CTRL,		0x1818 },
	{ SGTL5000_CHIP_ANA_CTRL,		0x0111 },
	{ SGTL5000_CHIP_REF_CTRL,		0x0000 },
	{ SGTL5000_CHIP_MIC_CTRL,		0x0000 },
	{ SGTL5000_CHIP_LINE_OUT_CTRL,		0x0000 },
	{ SGTL5000_CHIP_LINE_OUT_VOL,		0x0404 },
	{ SGTL5000_CHIP_PLL_CTRL,		0x5000 },
	{ SGTL5000_CHIP_CLK_TOP_CTRL,		0x0000 },
	{ SGTL5000_CHIP_ANA_STATUS,		0x0000 },
	{ SGTL5000_CHIP_SHORT_CTRL,		0x0000 },
	{ SGTL5000_CHIP_ANA_TEST2,		0x0000 },
	{ SGTL5000_DAP_CTRL,			0x0000 },
	{ SGTL5000_DAP_PEQ,			0x0000 },
	{ SGTL5000_DAP_BASS_ENHANCE,		0x0040 },
	{ SGTL5000_DAP_BASS_ENHANCE_CTRL,	0x051f },
	{ SGTL5000_DAP_AUDIO_EQ,		0x0000 },
	{ SGTL5000_DAP_SURROUND,		0x0040 },
	{ SGTL5000_DAP_EQ_BASS_BAND0,		0x002f },
	{ SGTL5000_DAP_EQ_BASS_BAND1,		0x002f },
	{ SGTL5000_DAP_EQ_BASS_BAND2,		0x002f },
	{ SGTL5000_DAP_EQ_BASS_BAND3,		0x002f },
	{ SGTL5000_DAP_EQ_BASS_BAND4,		0x002f },
	{ SGTL5000_DAP_MAIN_CHAN,		0x8000 },
	{ SGTL5000_DAP_MIX_CHAN,		0x0000 },
	{ SGTL5000_DAP_AVC_CTRL,		0x0510 },
	{ SGTL5000_DAP_AVC_THRESHOLD,		0x1473 },
	{ SGTL5000_DAP_AVC_ATTACK,		0x0028 },
	{ SGTL5000_DAP_AVC_DECAY,		0x0050 },
};


/*
 * Write all the default values from sgtl5000_reg_defaults[] array into the
 * sgtl5000 registers, to make sure we always start with the sane registers
 * values as stated in the datasheet.
 *
 * Since sgtl5000 does not have a reset line, nor a reset command in software,
 * we follow this approach to guarantee we always start from the default values
 * and avoid problems like, not being able to probe after an audio playback
 * followed by a system reset or a 'reboot' command in Linux
 */
static void sgtl5000_fill_defaults(struct i2c_client *client)
{
	struct sgtl5000_priv *sgtl5000 = i2c_get_clientdata(client);
	int i, ret, val, index;

	for (i = 0; i < ARRAY_SIZE(sgtl5000_reg_defaults); i++) {
		val = sgtl5000_reg_defaults[i].def;
		index = sgtl5000_reg_defaults[i].reg;
		ret = regmap_write(sgtl5000->regmap, index, val);
		if (ret)
			dev_err(&client->dev,
				"%s: error %d setting reg 0x%02x to 0x%04x\n",
				__func__, ret, index, val);
	}
}
